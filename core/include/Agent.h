#ifndef RUMMIKUB_CORE__AGENT_H
#define RUMMIKUB_CORE__AGENT_H

#include "CoreFwd.h"

#include "StdMemory.h"

namespace rummikub {

/**
 */
struct Agent {

  struct Delegate {
    virtual ~Delegate();
    virtual bool putTile(Tile, const cs_ptr<Set>& = cs_ptr<Set>{}) = 0;
    virtual bool moveTile(Tile, const cs_ptr<Set>&, const cs_ptr<Set>&) = 0;
    virtual const cs_ptr<Table> getTable() const = 0;
    virtual const cs_ptr<Hand> getHand() const = 0;
    virtual size_t countPut() const = 0;
    virtual bool validate() const = 0;
    virtual void restore() = 0;
  };

  virtual ~Agent();
  virtual void response(const s_ptr<Delegate>&) const = 0;
};

} // namespace rummikub

#endif // RUMMIKUB_CORE__AGENT_H

