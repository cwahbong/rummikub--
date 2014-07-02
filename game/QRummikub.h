#ifndef RUMMIKUB_GAME__QRUMMIKUB_H
#define RUMMIKUB_GAME__QRUMMIKUB_H

#include "QDelegate.h"

#include "CoreFwd.h"
#include "Agent.h"
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

  virtual void tileMoved(
      const cs_ptr<Player>&,
      const Tile&,
      const cs_ptr<Set>&,
      const cs_ptr<Set>&) override;

  virtual void restored(
      const cs_ptr<Player>&,
      const cs_ptr<Table>&) override;

  virtual void gameStarted() override;

  virtual void gameEnded() override;

  virtual void turnStarted(const cs_ptr<Player>&) override;

  virtual void turnEnded(const cs_ptr<Player>&) override;

  virtual void response(
      const s_ptr<Delegate>& sp_delegate) override;

signals:
  void rummiTilePut(
      const cs_ptr<Player>&,
      const Tile& tile,
      const cs_ptr<Set>& sp_set);

  void rummiTileMoved(
      const cs_ptr<Player>&,
      const Tile&,
      const cs_ptr<Set>&,
      const cs_ptr<Set>&);

  void rummiRestored(
      const cs_ptr<Player>&,
      const cs_ptr<Table>&);

  void rummiGameStarted();

  void rummiGameEnded();

  void rummiTurnStarted(const cs_ptr<Player>&);

  void rummiTurnEnded(const cs_ptr<Player>&);

  void readyForResponse(QDelegate*);

public slots:
  void rummiStartGame();

private:
  const s_ptr<EventReceiver>& _sp_eventReceiver;
  const s_ptr<Agent>& _sp_agent;
  u_ptr<Rummikub> _up_rummikub;
};

} // namespace game
} // namespace rummikub

#endif // RUMMIKUB_GAME__QRUMMIKUB_H
