#ifndef RUMMIKUB_CORE__AGENT_H
#define RUMMIKUB_CORE__AGENT_H

#include "CoreFwd.h"

#include "StdMemory.h"

namespace rummikub {

/**
 */
class Agent {
public:

  class Delegate {
  public:
    Delegate(const w_ptr<EventReceiver>&,
             const s_ptr<Table>&,
             const s_ptr<Hand>&);
    ~Delegate();
    bool putTile(Tile, const cs_ptr<Set>& = cs_ptr<Set>{});
    bool moveTile(Tile, const cs_ptr<Set>&, const cs_ptr<Set>&);
    const cs_ptr<Table> getTable() const;
    const cs_ptr<Hand> getHand() const;
    size_t countPut() const;
    bool validate() const;
    void restore();

  private:
    struct Member;
    const u_ptr<Member> _;
  };

public:
  virtual void response(const s_ptr<Delegate>&) = 0;
};

} // namespace rummikub

#endif // RUMMIKUB_CORE__AGENT_H

