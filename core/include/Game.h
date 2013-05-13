#ifndef RUMMIKUB_CORE__GAME_H
#define RUMMIKUB_CORE__GAME_H

#include "CoreFwd.h"
#include "StdMemory.h"

#include <vector>

namespace rummikub {
namespace core {

class Game {
  Game(const Game&) = delete;

public:
  ~Game();
  s_ptr<EventReceiver> getEventReceiver() const;

  friend void startGame(const s_ptr<EventReceiver>&, const std::vector<s_ptr<Agent>>&);

private:
  Game(const s_ptr<EventReceiver>&);

  struct Member;
  u_ptr<Member> _;
};

void startGame(const s_ptr<EventReceiver>&, const std::vector<s_ptr<Agent>>&);

} // namespace rummikub
} // namespace core

#endif // RUMMIKUB_CORE__GAME_H

