#ifndef RUMMIKUB_CORE__RUMMIKUB_H
#define RUMMIKUB_CORE__RUMMIKUB_H

#include "CoreFwd.h"

#include "Player.h"
#include "StdMemory.h"
#include "Util.h"

#include <functional>
#include <vector>

namespace rummikub {
namespace core {

class Rummikub {
public:
  typedef std::function<void(const cs_ptr<Player>)> TurnCallback;
  typedef std::function<void()> GameCallback;

public:
  Rummikub(const std::vector<s_ptr<Agent>>&);

  std::vector<w_ptr<Player>> getPlayers();

  void addTurnStartCallback(const s_ptr<TurnCallback>&);
  void addTurnEndCallback(const s_ptr<TurnCallback>&);
  void addGameEndCallback(const s_ptr<GameCallback>&);

  void delTurnStartCallback(const s_ptr<TurnCallback>&);
  void delTurnEndCallback(const s_ptr<TurnCallback>&);
  void delGameEndCallback(const s_ptr<GameCallback>&);

  void startGame();

private:
  struct Member;
  Member* _;
};

} // namespace core
} // namespace rmmikub

#endif // RUMMIKUB_CORE__RUMMIKUB_H

