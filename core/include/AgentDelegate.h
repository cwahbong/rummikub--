#ifndef RUMMIKUB_CORE__AGENTDELEGATE_H
#define RUMMIKUB_CORE__AGENTDELEGATE_H

#include "CoreFwd.h"
#include "StdMemory.h"

namespace rummikub {
namespace core {

class AgentDelegate {
public:
  AgentDelegate(const cw_ptr<Game>&,
                const s_ptr<Table>&,
                const s_ptr<Hand>&);
  ~AgentDelegate();
  bool putTile(Tile, const cs_ptr<Set>& = cs_ptr<Set>{});
  bool moveTile(Tile, const cs_ptr<Set>&, const cs_ptr<Set>&);
  const cs_ptr<Table> getTable() const;
  const cs_ptr<Hand> getHand() const;
  size_t countPut() const;
  bool validate() const;
  void restore();

private:
  struct Member;
  u_ptr<Member> _;
};

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__AGENTDELEGATE_H
