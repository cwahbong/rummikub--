#ifndef RUMMIKUB_GAME__QDELEGATE_H
#define RUMMIKUB_GAME__QDELEGATE_H

#include "Agent.h"
#include "CoreFwd.h"
#include "StdMemory.h"
#include "model/Tile.h"

#include <QObject>

namespace rummikub {
namespace game {

/*
 */
class QDelegate : public QObject
{
  Q_OBJECT

public:
  QDelegate(const s_ptr<Agent::Delegate>& sp_delegate);

signals:
  void endResponse();

public slots:

  void putTile(
      const Tile& tile,
      const cs_ptr<Set>& sp_set);

  void moveTile(
      const Tile& tile,
      const cs_ptr<Set>& sp_from,
      const cs_ptr<Set>& sp_to);

  void restore();

private:
  const s_ptr<Agent::Delegate> _sp_delegate;
};

} // game
} // rummikub

#endif // RUMMIKUB_GAME__QDELEGATE_H
