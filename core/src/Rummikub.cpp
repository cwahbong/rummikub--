#include "Rummikub.h"

#include "Agent.h"
#include "Player.h"
#include "Table.h"
#include "Tile.h"

#include <iostream>

using std::make_shared;
using std::shared_ptr;
using std::vector;
using std::weak_ptr;

namespace rummikub {
namespace core {

void
Rummikub::turnStart(const shared_ptr<const Player>& sp_player)
{
  for (const auto& callback : m_turnStartCallbacks) {
    callback(sp_player);
  }
}

void
Rummikub::turnEnd(const shared_ptr<const Player>& sp_player)
{
  for (const auto& callback : m_turnEndCallbacks) {
    callback(sp_player);
  }
}

void
Rummikub::gameEnd()
{
  for (const auto& callback : m_gameEndCallbacks) {
    callback();
  }
}

vector<weak_ptr<Player>>
Rummikub::getPlayers()
{
  return vector<weak_ptr<Player>>{m_sp_players.begin(), m_sp_players.end()};
}

shared_ptr<Notifier<Rummikub>>
Rummikub::getNotifier() const
{
  return m_sp_notifier;
}

void
Rummikub::addTurnStartCallback(TurnCallback c)
{
  m_turnStartCallbacks.push_back(c);
}

void
Rummikub::addTurnEndCallback(TurnCallback c)
{
  m_turnEndCallbacks.push_back(c);
}

void
Rummikub::addGameEndCallback(GameCallback c)
{
  m_gameEndCallbacks.push_back(c);
}

void
Rummikub::startGame()
{
  // get initial tiles.
  for (auto sp_player : m_sp_players) {
    for (unsigned i=0; i<14; ++i) {
      sp_player->addTile(m_sp_tileManager->getAndRemoveTile());
    }
  }
  // start turns loop
  while (true) {
    for (auto sp_player : m_sp_players) {
      turnStart(sp_player);
      const auto& sp_agent = sp_player->getAgent().lock();
      if (sp_agent) {
        auto sp_delegate = make_shared<AgentDelegate>(m_sp_table, sp_player);
        sp_agent->response(sp_delegate);
        if (!sp_delegate->validate()) {
          sp_delegate->restore();
          sp_player->addTile(m_sp_tileManager->getAndRemoveTile());
        } else if (sp_delegate->countPut() == 0) {
          sp_player->addTile(m_sp_tileManager->getAndRemoveTile());
        }
      } else {
        sp_player->addTile(m_sp_tileManager->getAndRemoveTile());
      }
      turnEnd(sp_player);
      if (sp_player->empty() || m_sp_tileManager->empty()) {
        gameEnd();
        return;
      }
    }
  }
}

} // namespace core
} // namespace rummikub

