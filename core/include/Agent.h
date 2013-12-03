#ifndef RUMMIKUB_CORE__AGENT_H
#define RUMMIKUB_CORE__AGENT_H

#include "CoreFwd.h"

#include "StdMemory.h"

namespace rummikub {

/*! \addtogroup rummicore
 *  @{
 */

/*! \brief An agent in rummikub game.
 *
 *  Agent may be AI, or provide an user interface to get the action
 *  taken by them.
 *  Though it is not suggested, you could assign same agent to different player.
 */
struct Agent {

  /*! \brief Provide available actions for agent.
   *  \ingroup rummicore
   */
  struct Delegate {
    virtual ~Delegate();

    /*! \brief Put a tile into a set on the table.
     *
     *  \param tile   the tile being put.
     *  \param sp_set the set.  If sp_set is an empty pointer then a
     *                new set is created.
     */
    virtual bool putTile(
        Tile tile,
        const cs_ptr<Set>& sp_set = cs_ptr<Set>{}) = 0;

    /*! \brief Move a tile from a set to another set.
     *
     *  \param tile
     */
    virtual bool moveTile(
        Tile tile,
        const cs_ptr<Set>& sp_from,
        const cs_ptr<Set>& sp_to) = 0;

    /*! \brief Getter.
     */
    virtual const cs_ptr<Table> getTable() const = 0;

    /*! \brief Getter.
     */
    virtual const cs_ptr<Hand> getHand() const = 0;

    /*! \brief Get the number of tiles put onto the table.
     */
    virtual size_t countPut() const = 0;

    /*! \brief Check if all of the sets on the table are valid.
     */
    virtual bool validate() const = 0;

    /*! \brief Restore the table, hand, and set, to the beginning of the
     * turn.
     */
    virtual void restore() = 0;
  };

  virtual ~Agent();

  /*! \brief Do some actions in a turn.
   */
  virtual void response(const s_ptr<Delegate>&) = 0;
};

/*! @} */

} // namespace rummikub

#endif // RUMMIKUB_CORE__AGENT_H

