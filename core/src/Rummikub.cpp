#include "Rummikub.h"

#include "model/Set.h"
#include "model/Table.h"
#include "model/Tile.h"
#include "model/Hand.h"
#include "Agent.h"
#include "EventReceiver.h"

#include <algorithm>
#include <map>
#include <set>

using std::const_pointer_cast;
using std::make_shared;
using std::map;
using std::random_shuffle;
using std::static_pointer_cast;
using std::set;
using std::vector;

namespace {

using rummikub::Tile;
using rummikub::RED;
using rummikub::BLUE;
using rummikub::YELLOW;
using rummikub::BLACK;

const unsigned INITIAL_HAND_NUM = 14;

vector<Tile> defaultTiles()
{
  vector<Tile> result;
  for (auto v = Tile::MIN_VALUE; v <= Tile::MAX_VALUE; ++v) {
    for(unsigned i = 0; i < 2; ++i) {
      result.push_back(Tile{RED, v});
      result.push_back(Tile{BLUE, v});
      result.push_back(Tile{YELLOW, v});
      result.push_back(Tile{BLACK, v});
    }
  }
  result.push_back(Tile::joker(RED));
  result.push_back(Tile::joker(BLACK));
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
           const s_ptr<Hand>& h)
    : wp_eventReceiver{er},
      csp_oldTable{make_shared<Table>(*t)},
      csp_oldHand{make_shared<Hand>(*h)},
      sp_table{t},
      sp_hand{h},
      put{0}
  {/* Empty. */}

  ~_AgentDelegate() {/* Empty. */}

  bool putTile(Tile tile, const cs_ptr<Set>& sp_set = cs_ptr<Set>{}) {
    if (!sp_hand->hasTile(tile)) return false;
    const auto& sp_newSet = const_pointer_cast<Set>(sp_set ? sp_set : sp_table->addSet());
    sp_newSet->insert(tile);
    wp_eventReceiver.lock()->tilePut(sp_hand, tile, sp_set);
    sp_hand->removeTile(tile);
    ++put;
    return true;
  }

  bool moveTile(Tile tile, const cs_ptr<Set>& sp_from, const cs_ptr<Set>& sp_to) {
    if (!sp_from || !sp_to) return false;
    if (!const_pointer_cast<Set>(sp_from)->remove(tile)) return false;
    sp_table->clean();
    const_pointer_cast<Set>(sp_to)->insert(tile);
    wp_eventReceiver.lock()->tileMoved(tile, sp_from, sp_to);
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
    wp_eventReceiver.lock()->restored(sp_table, sp_hand);
  }

private:
  const w_ptr<EventReceiver> wp_eventReceiver;
  const cs_ptr<Table> csp_oldTable;
  const cs_ptr<Hand> csp_oldHand;
  const s_ptr<Table> sp_table;
  const s_ptr<Hand> sp_hand;
  size_t put;
};

struct Rummikub::Member {
  const w_ptr<EventReceiver> wp_eventReceiver;
  s_ptr<_Pile<Tile>> sp_pileTiles;
  s_ptr<Table> sp_table;
  vector<s_ptr<Agent>> sp_agents;
  map<s_ptr<Agent>, s_ptr<Hand>> playerMap;

  void
  initHands()
  {
    for (const auto& sp_agent : sp_agents) {
      const auto& sp_player = playerMap[sp_agent];
      for (unsigned i = 0; i < INITIAL_HAND_NUM; ++i) {
        sp_player->addTile(sp_pileTiles->draw());
      }
    }
  }

  void
  turn(const s_ptr<Agent>& sp_agent)
  {
    const auto& sp_player = playerMap[sp_agent];
    auto sp_delegate = make_shared<_AgentDelegate>(wp_eventReceiver, sp_table, sp_player); // XXX
    sp_agent->response(sp_delegate);
    if (!sp_delegate->validate()) {
      sp_delegate->restore();
      sp_player->addTile(sp_pileTiles->draw());
    } else if (sp_delegate->countPut() == 0) {
      sp_player->addTile(sp_pileTiles->draw());
    }
  }
};

Rummikub::Rummikub(const w_ptr<EventReceiver>& wp_eventReceiver, const vector<s_ptr<Agent>>& agents)
  : _{new Member{
        wp_eventReceiver,
        make_shared<_Pile<Tile>>(defaultTiles()),
        make_shared<Table>()
    }}
{
  _->sp_pileTiles->shuffle();
  for (const auto& sp_agent : agents) {
    _->sp_agents.push_back(sp_agent);
    _->playerMap[sp_agent] = make_shared<Hand>();
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
  const auto& sp_eventReceiver = _->wp_eventReceiver.lock();
  sp_eventReceiver->gameStarted();
  while (true) {
    for (auto sp_agent : _->sp_agents) {
      auto sp_player = _->playerMap[sp_agent];
      sp_eventReceiver->turnStarted(sp_agent);
      _->turn(sp_agent);
      if (sp_player->empty() || _->sp_pileTiles->empty()) {
        sp_eventReceiver->gameEnded();
        return;
      }
      sp_eventReceiver->turnEnded(sp_agent);
    }
  }
}

} // namespace rummikub

