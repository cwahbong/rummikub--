#ifndef RUMMIKUB_CORE__AGENT_H
#define RUMMIKUB_CORE__AGENT_H

#include "CoreFwd.h"

#include <memory>

namespace rummikub {
namespace core {

/**
 */
class Agent {
public:
  virtual void response(const std::shared_ptr<const AgentDelegate>&) = 0;
};

class AgentDelegate {
private:
  const std::shared_ptr<const Table> m_sp_oldTable;
  const std::shared_ptr<const Player> m_sp_oldPlayer;
  const std::shared_ptr<Table> m_sp_table;
  const std::shared_ptr<Player> m_sp_player;

public:
  AgentDelegate(const std::shared_ptr<Table>& sp_table,
                const std::shared_ptr<Player>& sp_player);
  bool putTile(Tile, const std::shared_ptr<const Set>& = std::shared_ptr<const Set>{}) const;
  bool moveTile(Tile,
                const std::shared_ptr<const Set>&,
                const std::shared_ptr<const Set>&) const;
  const Table& getTable() const;
  const Player& getPlayer() const;
  bool validate() const;
  void restore() const;
};

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__AGENT_H

