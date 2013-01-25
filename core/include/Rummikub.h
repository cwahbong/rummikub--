#ifndef RUMMIKUB_CORE__RUMMIKUB_H
#define RUMMIKUB_CORE__RUMMIKUB_H

#include "CoreFwd.h"

#include "Table.h"

#include <functional>
#include <memory>
#include <vector>

namespace rummikub {
namespace core {

class Rummikub {
public:
  typedef std::function<void()> Callback;

private:
  std::shared_ptr<Table> m_sp_table;
  std::shared_ptr<AgentDelegate> m_sp_delegate;
  std::vector<std::shared_ptr<Player>> m_sp_players;
  std::vector<Callback> m_turnStartCallbacks;
  std::vector<Callback> m_turnEndCallbacks;
  std::vector<Callback> m_gameEndCallbacks;

  void turnStart();
  void turnEnd();
  void gameEnd();

public:
  template <typename InputIterator>
  Rummikub(InputIterator first, InputIterator last)
    : m_sp_table{Table::newTable()},
      m_sp_delegate{std::make_shared<AgentDelegate>(m_sp_table)},
      m_sp_players{first, last}
  {/* Empty. */}

  std::vector<std::weak_ptr<Player>> getPlayers();
  void addTurnStartCallback(Callback);
  void addTurnEndCallback(Callback);
  void addGameEndCallback(Callback);
  void startGame();
};

} // namespace core
} // namespace rmmikub

#endif // RUMMIKUB_CORE__RUMMIKUB_H

