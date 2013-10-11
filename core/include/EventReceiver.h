#ifndef RUMMIKUB_CORE__EVENTRECEIVER_H
#define RUMMIKUB_CORE__EVENTRECEIVER_H

#include "CoreFwd.h"
#include "StdMemory.h"

namespace rummikub {

/*! \addtogroup rummicore
 *  @{
 */

/*! \brief A collection of functions called when something happened in
 *         game.
 *
 *  All of the member functions are virtual with empty implementation.
 */
struct EventReceiver {
  virtual ~EventReceiver(
  ) {/* Empty. */}

  /*! Invoked when a tile is put into a set on the table. */
  virtual void tilePut(
      const cs_ptr<Player>&,
      const Tile&,
      const cs_ptr<Set>&
  ) {/* Empty. */}

  /*! Invoked when a tile is moved from a set to another set. */
  virtual void tileMoved(
      const cs_ptr<Player>&,
      const Tile&,
      const cs_ptr<Set>&,
      const cs_ptr<Set>&
  ) {/* Empty. */}

  /*! Invoked when actions of a round by an agent restored. */
  virtual void restored(
      const cs_ptr<Player>&,
      const cs_ptr<Table>&
  ) {/* Empty. */}

  /*! Invoked when the game is going to start. */
  virtual void gameStarted(
  ) {/* Empty. */}

  /*! Invoked when the game is going to end. */
  virtual void gameEnded(
  ) {/* Empty. */}

  /*! Invoked when a turn is going to start. */
  virtual void turnStarted(
    const cs_ptr<Player>&
  ) {/* Empty. */}

  /*! Invoked when a turn is going to end. */
  virtual void turnEnded(
    const cs_ptr<Player>&
  ) {/* Empty. */}
};

/*! @} */

} // namespace rummikub

#endif // RUMMIKUB_CORE__EVENTRECEIVER_H

