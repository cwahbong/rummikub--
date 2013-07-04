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
  Game(const s_ptr<EventReceiver>&, const std::vector<s_ptr<Agent>>&);
  ~Game();

  void start();

private:
  struct Member;
  const u_ptr<Member> _;
};

} // namespace rummikub
} // namespace core

#endif // RUMMIKUB_CORE__GAME_H

