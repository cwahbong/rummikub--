#include "Rummikub.h"

#include "Agent.h"
#include "Player.h"
#include "Table.h"

using std::vector;
using std::weak_ptr;

namespace rummikub {
namespace core {

void
Rummikub::turnStart()
{
  for (const auto& callback : m_turnStartCallbacks) {
    callback();
  }
}

void
Rummikub::turnEnd()
{
  for (const auto& callback : m_turnEndCallbacks) {
    callback();
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
Rummikub::addTurnStartCallback(Callback c)
{
  m_turnStartCallbacks.push_back(c);
}

void
Rummikub::addTurnEndCallback(Callback c)
{
  m_turnEndCallbacks.push_back(c);
}

void
Rummikub::addGameEndCallback(Callback c)
{
  m_gameEndCallbacks.push_back(c);
}

void
Rummikub::startGame()
{
  while (true) {
    for (auto sp_player : m_sp_players) {
      turnStart();
      sp_player->getAgent().lock()->response(m_sp_delegate, sp_player, m_sp_table);
      turnEnd();
      if (sp_player->empty()) {
        gameEnd();
        break;
      }
    }
  }
}

} // namespace core
} // namespace rummikub

