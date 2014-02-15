#include "QRummikub.h"

#include "Rummikub.h"

#include <map>
#include <string>
  using std::map;
  using std::string;
  using std::move;

#include <QWaitCondition>

namespace rummikub {
namespace game {

/*  QRummikub is a QObject.  It can not be passed as a shared pointer,
 *  or it will be freed by both s_ptr and its parent.
 */
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

class _AgentSharedGuard : public Agent {
public:
  _AgentSharedGuard(Agent* agent)
    : _agent(agent)
  {/* Empty. */}

  virtual void response(
      const s_ptr<Delegate>& sp_delegate) override
  {
    _agent->response(sp_delegate);
  }

private:
  Agent* const _agent;
};

QRummikub::QRummikub(
    map<string, s_ptr<Agent>> players,
    QObject* parent)
  : QObject(parent),
    EventReceiver(),
    Agent(),
    _sp_eventReceiver(make_s<_EventReceiverSharedGuard>(this)),
    _sp_agent(make_s<_AgentSharedGuard>(this))
{
  for (auto& pair : players) {
    if (pair.second == nullptr) {
      pair.second = _sp_agent;
    }
  }
  _up_rummikub = u_ptr<Rummikub>(new Rummikub(_sp_eventReceiver, players));
}

QRummikub::~QRummikub()
{/* Empty. */}

void
QRummikub::tilePut(
    const cs_ptr<Player>& sp_player,
    const Tile& tile,
    const cs_ptr<Set>& sp_set)
{
  emit rummiTilePut(sp_player, tile, sp_set);
}

void
QRummikub::tileMoved(
    const cs_ptr<Player>& sp_player,
    const Tile& tile,
    const cs_ptr<Set>& sp_set_from,
    const cs_ptr<Set>& sp_set_to)
{
  emit rummiTileMoved(sp_player, tile, sp_set_from, sp_set_to);
}

void
QRummikub::restored(
    const cs_ptr<Player>& sp_player,
    const cs_ptr<Table>& sp_table)
{
  emit rummiRestored(sp_player, sp_table);
}

void
QRummikub::gameStarted()
{
  emit rummiGameStarted();
}

void
QRummikub::gameEnded()
{
  emit rummiGameEnded();
}

void
QRummikub::turnStarted(const cs_ptr<Player>& sp_player)
{
  emit rummiTurnStarted(sp_player);
}

void
QRummikub::turnEnded(const cs_ptr<Player>& sp_player)
{
  emit rummiTurnEnded(sp_player);
}

void
QRummikub::response(
    const s_ptr<Delegate>& sp_delegate)
{
  _rummiMutex.lock();
  QDelegate qDelegate(sp_delegate, &_rummiMutex, &_rummiWaitCondition);
  emit readyForResponse(&qDelegate);
  _rummiWaitCondition.wait(&_rummiMutex);
  _rummiMutex.unlock();
}

void
QRummikub::rummiStartGame()
{
  _up_rummikub->startGame();
}

} // namespace game
} // namespace rummikub
