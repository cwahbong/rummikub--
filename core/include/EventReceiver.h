#ifndef RUMMIKUB_CORE__EVENTRECEIVER_H
#define RUMMIKUB_CORE__EVENTRECEIVER_H

#include "CoreFwd.h"
#include "StdMemory.h"

namespace rummikub {

struct EventReceiver {
  // Invoked by Agent::Delegate.
  virtual void tilePut(
      const cs_ptr<Player>&,
      const Tile&,
      const cs_ptr<Set>&
  ) {/* Empty. */}
  virtual void tileMoved(
      const cs_ptr<Player>&,
      const Tile&,
      const cs_ptr<Set>&,
      const cs_ptr<Set>&
  ) {/* Empty. */}
  virtual void restored(
      const cs_ptr<Player>&,
      const cs_ptr<Table>&
  ) {/* Empty. */}

  // Invoke by rummikub
  virtual void gameStarted(
  ) {/* Empty. */}
  virtual void gameEnded(
  ) {/* Empty. */}
  virtual void turnStarted(
    const cs_ptr<Player>&
  ) {/* Empty. */}
  virtual void turnEnded(
    const cs_ptr<Player>&
  ) {/* Empty. */}
};

} // namespace rummikub

#endif // RUMMIKUB_CORE__EVENTRECEIVER_H

