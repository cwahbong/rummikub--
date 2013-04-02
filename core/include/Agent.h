#ifndef RUMMIKUB_CORE__AGENT_H
#define RUMMIKUB_CORE__AGENT_H

#include "CoreFwd.h"

#include "StdMemory.h"

namespace rummikub {
namespace core {

/**
 */
class Agent {
public:
  virtual void response(const s_ptr<AgentDelegate>&) = 0;
};

class AgentDelegate {
public:
  AgentDelegate(const s_ptr<Table>&,
                const s_ptr<Player>&);
  bool putTile(Tile, const cs_ptr<Set>& = cs_ptr<Set>{});
  bool moveTile(Tile, const cs_ptr<Set>&, const cs_ptr<Set>&);
  const cs_ptr<Table> getTable() const;
  const cs_ptr<Player> getPlayer() const;
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

