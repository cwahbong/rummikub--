#ifndef RUMMIKUB_CORE__PLAYER_H
#define RUMMIKUB_CORE__PLAYER_H

#include "CoreFwd.h"

#include "StdMemory.h"

#include <string>

namespace rummikub {

class Player final {
  Player(Player&&) = delete;
  Player& operator=(Player&&) = delete;

public:
  Player(const std::string&, const cs_ptr<Agent>&);
  ~Player();

  std::string getId() const;
  cs_ptr<Agent> getAgent() const;
  s_ptr<Hand> getHand();

private:
  struct Member;
  const u_ptr<Member> _;
};

} // namespace rummikub

#endif // RUMMIKUB_CORE__PLAYER_H

