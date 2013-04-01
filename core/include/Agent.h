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
  virtual void response(const std::shared_ptr<AgentDelegate>&) = 0;
};

class AgentDelegate {
public:
  AgentDelegate(const std::shared_ptr<Table>& sp_table,
                const std::shared_ptr<Player>& sp_player);
  bool putTile(Tile, const std::shared_ptr<const Set>& = std::shared_ptr<const Set>{});
  bool moveTile(Tile,
                const std::shared_ptr<const Set>&,
                const std::shared_ptr<const Set>&);
  const Table& getTable() const;
  const Player& getPlayer() const;
  size_t countPut() const;
  bool validate() const;
  void restore();

private:
  struct Member;
  Member* _;
};

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__AGENT_H

