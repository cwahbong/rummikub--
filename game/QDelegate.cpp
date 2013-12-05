#include "QDelegate.h"

namespace rummikub {
namespace game {

QDelegate::QDelegate(
    const s_ptr<Agent::Delegate>& sp_delegate,
    QMutex* p_mutex,
    QWaitCondition* p_waitCondition)
  : _sp_delegate(sp_delegate),
    _p_mutex(p_mutex),
    _p_waitCondition(p_waitCondition)
{/* Empty. */}

void
QDelegate::startResponse()
{
  _p_mutex->lock();
}

void
QDelegate::endResponse()
{
  _p_mutex->unlock();
  _p_waitCondition->wakeAll();
}

void
QDelegate::putTile(
    Tile tile,
    const cs_ptr<Set>& sp_set)
{
  _sp_delegate->putTile(tile, sp_set);
}

void
QDelegate::moveTile(
    Tile tile,
    const cs_ptr<Set>& sp_from,
    const cs_ptr<Set>& sp_to)
{
  _sp_delegate->moveTile(tile, sp_from, sp_to);
}

void
QDelegate::restore()
{
  _sp_delegate->restore();
}

} // namespace game
} // namespace rummikub
