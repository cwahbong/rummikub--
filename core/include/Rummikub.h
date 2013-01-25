#ifndef RUMMIKUB_CORE__RUMMIKUB_H
#define RUMMIKUB_CORE__RUMMIKUB_H

#include "CoreFwd.h"

#include "Table.h"
#include "TileManager.h"

#include <functional>
#include <memory>
#include <vector>

namespace rummikub {
namespace core {

class Rummikub {
public:
  typedef std::function<void(const std::shared_ptr<const Player>)> TurnCallback;
  typedef std::function<void()> GameCallback;

private:
  std::shared_ptr<TileManager> m_sp_tileManager;
  std::shared_ptr<Table> m_sp_table;
  std::vector<std::shared_ptr<Player>> m_sp_players;
  std::vector<TurnCallback> m_turnStartCallbacks;
  std::vector<TurnCallback> m_turnEndCallbacks;
  std::vector<GameCallback> m_gameEndCallbacks;

  void turnStart(const std::shared_ptr<const Player>&);
  void turnEnd(const std::shared_ptr<const Player>&);
  void gameEnd();

public:
  Rummikub(std::vector<std::shared_ptr<Player>>::size_type playerNum);

  std::vector<std::weak_ptr<Player>> getPlayers();
  void addTurnStartCallback(TurnCallback);
  void addTurnEndCallback(TurnCallback);
  void addGameEndCallback(GameCallback);
  void startGame();
};

} // namespace core
} // namespace rmmikub

#endif // RUMMIKUB_CORE__RUMMIKUB_H

