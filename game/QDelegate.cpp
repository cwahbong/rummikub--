#include "QDelegate.h"

#include <QDebug>

namespace rummikub {
namespace game {

QDelegate::QDelegate(const s_ptr<Agent::Delegate>& sp_delegate)
  : _sp_delegate(sp_delegate)
{/* Empty. */}

void
QDelegate::putTile(
    const Tile& tile,
    const cs_ptr<Set>& sp_set)
{
  qDebug() << "QDelegate put tile.\n";
  _sp_delegate->putTile(tile, sp_set);
}

void
QDelegate::moveTile(
    const Tile& tile,
    const cs_ptr<Set>& sp_from,
    const cs_ptr<Set>& sp_to)
{
  qDebug() << "QDelegate move tile.\n";
  _sp_delegate->moveTile(tile, sp_from, sp_to);
}

void
QDelegate::restore()
{
  _sp_delegate->restore();
}

} // namespace game
} // namespace rummikub
