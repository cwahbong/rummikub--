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
  virtual void response(const std::shared_ptr<const AgentDelegate>&,
                        const std::shared_ptr<const Player>&,
                        const std::shared_ptr<const Table>&) = 0;
};

class AgentDelegate {
private:
  std::shared_ptr<Table> m_sp_table;

public:
  AgentDelegate(const std::shared_ptr<Table>& sp_table) : m_sp_table{sp_table} {}
  bool putTile(Tile, const std::shared_ptr<const Set>&);
  bool moveTile(Tile, const std::shared_ptr<const Set>&, const std::shared_ptr<const Set>&);
};

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__AGENT_H

