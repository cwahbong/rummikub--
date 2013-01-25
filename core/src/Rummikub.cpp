#include "Rummikub.h"

#include "Agent.h"
#include "Player.h"
#include "Table.h"
#include "Tile.h"

using std::make_shared;
using std::shared_ptr;
using std::vector;
using std::weak_ptr;

namespace rummikub {
namespace core {

Rummikub::Rummikub(std::vector<std::shared_ptr<Player>>::size_type playerNum)
  : m_sp_tileManager{TileManager::newShuffledTiles()},
    m_sp_table{Table::newTable()},
    m_sp_players{playerNum},
    m_turnStartCallbacks{},
    m_turnEndCallbacks{},
    m_gameEndCallbacks{}
{
  for (auto& sp_player : m_sp_players) {
    sp_player = Player::newPlayer();
  }
}

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
  // TODO get initial tiles.

  while (true) {
    for (auto sp_player : m_sp_players) {
      turnStart(sp_player);
      const auto& sp_agent = sp_player->getAgent().lock();
      if (sp_agent) {
        auto sp_delegate = make_shared<AgentDelegate>(m_sp_table, sp_player);
        sp_agent->response(sp_delegate, sp_player, m_sp_table);
        if (!sp_delegate->validate()) {
          sp_delegate->restore();
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

