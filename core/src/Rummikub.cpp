#include "model/Rummikub.h"

#include "model/Table.h"
#include "model/Tile.h"
#include "Agent.h"
#include "AgentDelegate.h"
#include "Game.h"
#include "EventReceiver.h"
#include "TileManager.h"

#include <map>
#include <set>

using std::const_pointer_cast;
using std::make_shared;
using std::map;
using std::static_pointer_cast;
using std::set;
using std::vector;

namespace rummikub {
namespace core {

struct Rummikub::Member {
  const cw_ptr<Game> wp_game;
  s_ptr<TileManager> sp_tileManager;
  s_ptr<Table> sp_table;
  vector<s_ptr<Agent>> sp_agents;
  map<s_ptr<Agent>, s_ptr<Player>> playerMap;

  void
  initPlayers()
  {
    for (const auto& sp_agent : sp_agents) {
      const auto& sp_player = playerMap[sp_agent];
      for (unsigned i=0; i<14; ++i) {
        sp_player->addTile(sp_tileManager->drawTile());
      }
    }
  }

  void
  turn(const s_ptr<Agent>& sp_agent)
  {
    const auto& sp_player = playerMap[sp_agent];
    auto sp_delegate = make_shared<AgentDelegate>(wp_game, sp_table, sp_player); // XXX
    sp_agent->response(sp_delegate);
    if (!sp_delegate->validate()) {
      sp_delegate->restore();
      sp_player->addTile(sp_tileManager->drawTile());
    } else if (sp_delegate->countPut() == 0) {
      sp_player->addTile(sp_tileManager->drawTile());
    }
  }
};

Rummikub::Rummikub(const cw_ptr<Game>& wp_game, const vector<s_ptr<Agent>>& agents)
  : _{new Member{
        wp_game,
        make_shared<TileManager>(),
        make_shared<Table>(wp_game)
    }}
{
  _->sp_tileManager->shuffle();
  for (const auto& sp_agent : agents) {
    _->sp_agents.push_back(sp_agent);
    _->playerMap[sp_agent] = make_shared<Player>(wp_game);
  }
}

Rummikub::~Rummikub()
{
  delete _;
}

s_ptr<Table>
Rummikub::getTable()
{
  return const_pointer_cast<Table>(static_cast<const Rummikub*>(this)->getTable());
}

cs_ptr<Table>
Rummikub::getTable() const
{
  return _->sp_table;
}

vector<s_ptr<Player>>
Rummikub::getPlayers()
{
  // XXX using playerMap instead
  // return vector<s_ptr<Player>>{_->sp_players.begin(), _->sp_players.end()};
}

vector<cs_ptr<Player>>
Rummikub::getPlayers() const
{
  //return vector<cs_ptr<Player>>{_->sp_players.begin(), _->sp_players.end()};
}

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
  _->initPlayers();
  const auto& sp_eventReceiver = _->wp_game.lock()->getEventReceiver();
  sp_eventReceiver->gameStarted();
  while (true) {
    for (auto sp_agent : _->sp_agents) {
      auto sp_player = _->playerMap[sp_agent];
      sp_eventReceiver->turnStarted(sp_agent);
      _->turn(sp_agent);
      if (sp_player->empty() || _->sp_tileManager->empty()) {
        sp_eventReceiver->gameEnded();
        return;
      }
      sp_eventReceiver->turnEnded(sp_agent);
    }
  }
}

} // namespace core
} // namespace rummikub

