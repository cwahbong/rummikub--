#ifndef RUMMIKUB_GAME__QDELEGATE_H
#define RUMMIKUB_GAME__QDELEGATE_H

#include "Agent.h"
#include "CoreFwd.h"
#include "StdMemory.h"
#include "model/Tile.h"

#include <QWidget>

namespace rummikub {
namespace game {

class QDelegate : public QWidget
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

  // const cs_ptr<Table> getTable() const = 0;

  // virtual const cs_ptr<Hand> getHand() const = 0;

  // virtual size_t countPut() const = 0;

  // virtual bool validate() const = 0;

private:
  const s_ptr<Agent::Delegate> _sp_delegate;
};

} // game
} // rummikub

#endif // RUMMIKUB_GAME__QDELEGATE_H
