#include "Rummikub.h"

#include "model/Set.h"
#include "model/Table.h"
#include "model/Tile.h"
#include "model/Hand.h"
#include "Agent.h"
#include "EventReceiver.h"
#include "Player.h"

#include <algorithm>
#include <set>

using std::const_pointer_cast;
using std::map;
using std::random_shuffle;
using std::static_pointer_cast;
using std::set;
using std::string;
using std::vector;

namespace {

using rummikub::Tile;

using Color = Tile::Color;
using Value = Tile::Value;

const unsigned INITIAL_HAND_NUM = 14;

vector<Tile> defaultTiles()
{
  vector<Tile> result;
  for (auto v = Tile::minValue(); v <= Tile::maxValue(); ++v) {
    for(unsigned i = 0; i < 2; ++i) {
      result.push_back(Tile{Color::RED, v});
      result.push_back(Tile{Color::BLUE, v});
      result.push_back(Tile{Color::YELLOW, v});
      result.push_back(Tile{Color::BLACK, v});
    }
  }
  result.push_back(Tile::jokerTile(Color::RED));
  result.push_back(Tile::jokerTile(Color::BLACK));
  return result;
}

template <typename T>
class _Pile {
public:

  _Pile(const vector<T>& ts) : _ts(ts)
  {/* Empty. */}

  T draw() {
    auto result = _ts.back();
    _ts.pop_back();
    return result;
  }

  bool empty() const {
    return _ts.empty();
  }

  void shuffle() {
    random_shuffle(_ts.begin(), _ts.end());
  }

private:
  vector<T> _ts;
};

}

namespace rummikub {

class _AgentDelegate final : public Agent::Delegate {
public:
  _AgentDelegate(const w_ptr<EventReceiver>& er,
                 const s_ptr<Table>& t,
                 const s_ptr<Player>& p)
    : wp_eventReceiver{er},
      csp_oldTable{make_s<Table>(*t)},
      csp_oldHand{make_s<Hand>(*p->getHand())},
      sp_player{p},
      sp_table{t},
      sp_hand{p->getHand()},
      put{0}
  {/* Empty. */}

  ~_AgentDelegate() {/* Empty. */}

  bool putTile(Tile tile, const cs_ptr<Set>& sp_set = cs_ptr<Set>{}) {
    if (!sp_hand->hasTile(tile)) return false;
    const auto& sp_newSet = const_pointer_cast<Set>(sp_set ? sp_set : sp_table->addSet());
    sp_newSet->insert(tile);
    wp_eventReceiver.lock()->tilePut(sp_player, tile, sp_newSet);
    sp_hand->removeTile(tile);
    ++put;
    return true;
  }

  bool moveTile(Tile tile, const cs_ptr<Set>& sp_from, const cs_ptr<Set>& sp_to) {
    if (!sp_from) return false;
    const auto& sp_newTo = const_pointer_cast<Set>(sp_to ? sp_to : sp_table->addSet());
    const_pointer_cast<Set>(sp_newTo)->insert(tile);
    if (!const_pointer_cast<Set>(sp_from)->remove(tile)) return false;
    sp_table->clean();
    wp_eventReceiver.lock()->tileMoved(sp_player, tile, sp_from, sp_newTo);
    return true;
  }

  const cs_ptr<Table> getTable() const {
    return sp_table;
  }

  const cs_ptr<Hand> getHand() const {
    return sp_hand;
  }

  size_t countPut() const {
    return put;
  }

  bool validate() const {
    for (const auto& wp_set : sp_table->getSets()) {
      if (wp_set.lock()->getType() == Set::NONE) {
        return false;
      }
    }
    return true;
  }

  void restore() {
    *sp_table = *csp_oldTable;
    *sp_hand = *csp_oldHand;
    put = 0;
    wp_eventReceiver.lock()->restored(sp_player, sp_table);
  }

private:
  const w_ptr<EventReceiver> wp_eventReceiver;
  const cs_ptr<Table> csp_oldTable;
  const cs_ptr<Hand> csp_oldHand;
  const s_ptr<Player> sp_player;
  const s_ptr<Table> sp_table;
  const s_ptr<Hand> sp_hand;
  size_t put;
};

struct Rummikub::Member {
  const s_ptr<EventReceiver> sp_eventReceiver;
  s_ptr<_Pile<Tile>> sp_pileTiles;
  s_ptr<Table> sp_table;
  vector<s_ptr<Player>> sp_players;

  void
  initHands()
  {
    for (const auto& sp_player : sp_players) {
      const auto& sp_hand = sp_player->getHand();
      for (unsigned i = 0; i < INITIAL_HAND_NUM; ++i) {
        sp_hand->addTile(sp_pileTiles->draw());
      }
    }
  }

  void
  turn(const s_ptr<Player>& sp_player)
  {
    const auto& sp_agent = sp_player->getAgent();
    const auto& sp_hand = sp_player->getHand();
    auto sp_delegate = make_s<_AgentDelegate>(sp_eventReceiver, sp_table, sp_player); // XXX
    sp_agent->response(sp_delegate);
    if (!sp_delegate->validate()) {
      sp_delegate->restore();
      sp_hand->addTile(sp_pileTiles->draw());
    } else if (sp_delegate->countPut() == 0) {
      sp_hand->addTile(sp_pileTiles->draw());
    }
  }
};

Rummikub::Rummikub(const s_ptr<EventReceiver>& sp_eventReceiver,
                   const map<string, s_ptr<Agent>>& sp_playerInfos)
  : _{new Member{
        sp_eventReceiver,
        make_s<_Pile<Tile>>(defaultTiles()),
        make_s<Table>()
    }}
{
  _->sp_pileTiles->shuffle();
  for (const auto& info : sp_playerInfos) {
    _->sp_players.push_back(make_s<Player>(info.first, info.second));
  }
}

Rummikub::~Rummikub()
{/* Empty.*/}

// Message Types:
/*
    1. Game start
    2. Turn start (player)
    3. Turn end (player)
    4. Game end
 */

void
Rummikub::startGame()
{
  _->initHands();
  _->sp_eventReceiver->gameStarted();
  while (true) {
    for (const auto& sp_player : _->sp_players) {
      const auto& sp_agent = sp_player->getAgent();
      _->sp_eventReceiver->turnStarted(sp_player);
      _->turn(sp_player);
      if (sp_player->getHand()->empty() || _->sp_pileTiles->empty()) {
        _->sp_eventReceiver->gameEnded();
        return;
      }
      _->sp_eventReceiver->turnEnded(sp_player);
    }
  }
}

} // namespace rummikub

