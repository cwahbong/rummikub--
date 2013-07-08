#ifndef RUMMIKUB_CORE__EVENTRECEIVER_H
#define RUMMIKUB_CORE__EVENTRECEIVER_H

#include "CoreFwd.h"
#include "StdMemory.h"

namespace rummikub {

struct EventReceiver {
  // for player
  virtual void tilePut(
      const cs_ptr<Hand>&,
      const Tile&,
      const cs_ptr<Set>&
  ) {/* Empty. */}
  virtual void tileMoved(
      const Tile&,
      const cs_ptr<Set>&,
      const cs_ptr<Set>&
  ) {/* Empty. */}
  virtual void restored(
      const cs_ptr<Table>&,
      const cs_ptr<Hand>&
  ) {/* Empty. */}

  // for table
  virtual void setAdded(
      const cs_ptr<Set>&
  ) {/* Empty. */}

  // for rummikub
  virtual void gameStarted(
  ) {/* Empty. */}
  virtual void gameEnded(
  ) {/* Empty. */}
  virtual void turnStarted(
    const cs_ptr<Agent>&
  ) {/* Empty. */}
  virtual void turnEnded(
    const cs_ptr<Agent>&
  ) {/* Empty. */}
};

} // namespace rummikub

#endif // RUMMIKUB_CORE__EVENTRECEIVER_H

