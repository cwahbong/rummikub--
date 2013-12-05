#ifndef RUMMIKUB_GAME__QRUMMIKUB_H
#define RUMMIKUB_GAME__QRUMMIKUB_H

#include "QDelegate.h"

#include "CoreFwd.h"
#include "Agent.h"
#include "EventReceiver.h"
#include "StdMemory.h"

#include <QMutex>
#include <QWaitCondition>
#include <QObject>

#include <map>
#include <string>
  using std::map;
  using std::string;

namespace rummikub {
namespace game {

class QRummikub : public QObject,
                  public EventReceiver,
                  public Agent
{
  Q_OBJECT
  QRummikub(const QRummikub&) = delete;

public:
  explicit QRummikub(std::map<std::string, s_ptr<Agent>>, QObject *parent = 0);
  ~QRummikub();

  virtual void tilePut(
      const cs_ptr<Player>&,
      const Tile&,
      const cs_ptr<Set>&) override;

  // TODO other events in EventReceiver

  virtual void response(
      const s_ptr<Delegate>& sp_delegate) override;

signals:
  void rummiTilePut(
    const cs_ptr<Player>&,
    const Tile& tile,
    const cs_ptr<Set>& sp_set);
  // TODO  other events in EventReceiver

  void readyForResponse(QDelegate*);

public slots:
  void rummiStartGame();

private:
  const s_ptr<EventReceiver>& _sp_eventReceiver;
  const s_ptr<Agent>& _sp_agent;
  u_ptr<Rummikub> _up_rummikub;
  QMutex _rummiMutex;
  QWaitCondition _rummiWaitCondition;
};

} // namespace game
} // namespace rummikub

#endif // RUMMIKUB_GAME__QRUMMIKUB_H
