#include "model/Rummikub.h"

#include "model/Table.h"
#include "model/Tile.h"
#include "Agent.h"
#include "TileManager.h"

#include <set>

using std::const_pointer_cast;
using std::make_shared;
using std::static_pointer_cast;
using std::set;
using std::vector;

namespace rummikub {
namespace core {

struct Rummikub::Member {
  s_ptr<TileManager> sp_tileManager;
  s_ptr<Table> sp_table;
  vector<s_ptr<Player>> sp_players;
  set<s_ptr<TurnCallback>> turnStartCallbacks;
  set<s_ptr<TurnCallback>> turnEndCallbacks;
  set<s_ptr<GameCallback>> gameEndCallbacks;

  void initPlayers()
  {
    for (auto sp_player : sp_players) {
      for (unsigned i=0; i<14; ++i) {
        sp_player->addTile(sp_tileManager->getAndRemoveTile());
      }
    }
  }

  void
  turnStart(const cs_ptr<Player>& sp_player)
  {
    for (const auto& sp_callback : turnStartCallbacks) {
      (*sp_callback)(sp_player);
    }
  }

  void
  turnEnd(const cs_ptr<Player>& sp_player)
  {
    for (const auto& sp_callback : turnEndCallbacks) {
      (*sp_callback)(sp_player);
    }
  }

  void gameEnd()
  {
    for (const auto& sp_callback : gameEndCallbacks) {
      (*sp_callback)();
    }
  }
};

Rummikub::Rummikub(const vector<s_ptr<Agent>>& agents)
  : _{new Member{make_shared<TileManager>(), Table::newTable()}}
{
  _->sp_tileManager->shuffle();
  for (const auto& sp_agent : agents) {
    const auto& sp_player = Player::newPlayer();
    sp_player->setAgent(sp_agent);
    _->sp_players.push_back(sp_player);
  }
}

Rummikub::~Rummikub()
{
  delete _;
}

void
Rummikub::addTurnStartCallback(const s_ptr<TurnCallback>& callback)
{
  _->turnStartCallbacks.insert(callback);
}

void
Rummikub::addTurnEndCallback(const s_ptr<TurnCallback>& callback)
{
  _->turnEndCallbacks.insert(callback);
}

void
Rummikub::addGameEndCallback(const s_ptr<GameCallback>& callback)
{
  _->gameEndCallbacks.insert(callback);
}

void
Rummikub::delTurnStartCallback(const s_ptr<TurnCallback>& callback)
{
  _->turnStartCallbacks.erase(callback);
}

void
Rummikub::delTurnEndCallback(const s_ptr<TurnCallback>& callback)
{
  _->turnEndCallbacks.erase(callback);
}

void
Rummikub::delGameEndCallback(const s_ptr<GameCallback>& callback)
{
  _->gameEndCallbacks.erase(callback);
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
  return vector<s_ptr<Player>>{_->sp_players.begin(), _->sp_players.end()};
}

vector<cs_ptr<Player>>
Rummikub::getPlayers() const
{
  return vector<cs_ptr<Player>>{_->sp_players.begin(), _->sp_players.end()};
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
  // TODO notify the callbacks that the game is started.
  // start turns loop
  while (true) {
    for (auto sp_player : _->sp_players) {
      _->turnStart(sp_player);
      const auto& sp_agent = sp_player->getAgent().lock();
      if (sp_agent) {
        auto sp_delegate = make_shared<AgentDelegate>(_->sp_table, sp_player);
        sp_agent->response(sp_delegate);
        if (!sp_delegate->validate()) {
          sp_delegate->restore();
          sp_player->addTile(_->sp_tileManager->getAndRemoveTile());
        } else if (sp_delegate->countPut() == 0) {
          sp_player->addTile(_->sp_tileManager->getAndRemoveTile());
        }
      } else {
        sp_player->addTile(_->sp_tileManager->getAndRemoveTile());
      }
      _->turnEnd(sp_player);
      if (sp_player->empty() || _->sp_tileManager->empty()) {
        _->gameEnd();
        return;
      }
    }
  }
}

} // namespace core
} // namespace rummikub

