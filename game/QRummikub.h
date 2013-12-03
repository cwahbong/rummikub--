#ifndef RUMMIKUB_GAME__QRUMMIKUB_H
#define RUMMIKUB_GAME__QRUMMIKUB_H

#include "CoreFwd.h"
#include "EventReceiver.h"
#include "StdMemory.h"

#include <QObject>

#include <map>
#include <string>
  using std::map;
  using std::string;

namespace rummikub {
namespace game {

class QRummikub : public QObject,
                  public EventReceiver
{
  Q_OBJECT
  QRummikub(const QRummikub&) = delete;

public:
  explicit QRummikub(QObject *parent = 0);
  ~QRummikub();

  void setRummikub(u_ptr<Rummikub>&& up_rummikub);

  virtual void tilePut(
      const cs_ptr<Player>&,
      const Tile& tile,
      const cs_ptr<Set>& sp_set);

signals:
  void rummiTilePut(
    const cs_ptr<Player>&,
    const Tile& tile,
    const cs_ptr<Set>& sp_set);
  // TODO  other events in EventReceiver

public slots:
  void rummiStartGame();

private:
  u_ptr<Rummikub> _up_rummikub;
};

} // namespace game
} // namespace rummikub

#endif // RUMMIKUB_GAME__QRUMMIKUB_H
