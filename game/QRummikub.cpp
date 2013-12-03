#include "QRummikub.h"

#include "Rummikub.h"

#include <map>
#include <string>
  using std::map;
  using std::string;
  using std::move;

namespace rummikub {
namespace game {

/*  QRummikub is a QObject.  It can not be passed as a shared pointer,
 *  or it will be freed by both s_ptr and its parent.
 */
#if 0
class _EventReceiverSharedGuard : public EventReceiver {
public:
  explicit _EventReceiverSharedGuard(EventReceiver* receiver)
    : _receiver(receiver)
  {/* Empty. */}

  virtual void tilePut(
    const cs_ptr<Player>& sp_player,
    const Tile& tile,
    const cs_ptr<Set>& sp_set) override
  {
    _receiver->tilePut(sp_player, tile, sp_set);
  }

  virtual void tileMoved(
      const cs_ptr<Player>& sp_player,
      const Tile& tile,
      const cs_ptr<Set>& sp_from,
      const cs_ptr<Set>& sp_to) override
  {
    _receiver->tileMoved(sp_player, tile, sp_from, sp_to);
  }

  virtual void restored(
      const cs_ptr<Player>& sp_player,
      const cs_ptr<Table>& sp_table) override
  {
    _receiver->restored(sp_player, sp_table);
  }

  virtual void gameStarted() override
  {
    _receiver->gameStarted();
  }

  virtual void gameEnded() override
  {
    _receiver->gameEnded();
  }

  virtual void turnStarted(
      const cs_ptr<Player>& sp_player) override
  {
    _receiver->turnStarted(sp_player);
  }

  virtual void turnEnded(
      const cs_ptr<Player>& sp_player) override
  {
    _receiver->turnEnded(sp_player);
  }

private:
  EventReceiver* const _receiver;
};
#endif

QRummikub::QRummikub(
    QObject* parent)
  : QObject(parent)
{/* Empty. */}

QRummikub::~QRummikub()
{/* Empty. */}

void
QRummikub::setRummikub(u_ptr<Rummikub>&& up_rummikub)
{
  _up_rummikub = move(up_rummikub);
}

void
QRummikub::tilePut(
    const cs_ptr<Player>& sp_player,
    const Tile& tile,
    const cs_ptr<Set>& sp_set)
{
  emit rummiTilePut(sp_player, tile, sp_set);
}

void
QRummikub::rummiStartGame()
{
  _up_rummikub->startGame();
}

} // namespace game
} // namespace rummikub
