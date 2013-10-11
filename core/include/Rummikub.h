#ifndef RUMMIKUB_CORE__RUMMIKUB_H
#define RUMMIKUB_CORE__RUMMIKUB_H

#include "CoreFwd.h"

#include "StdMemory.h"

#include <map>

namespace rummikub {

class Rummikub {
public:
  Rummikub(const s_ptr<EventReceiver>&, const std::map<std::string, s_ptr<Agent>>&);
  ~Rummikub();

  void startGame();

private:
  struct Member;
  const u_ptr<Member> _;
};

} // namespace rmmikub

#endif // RUMMIKUB_CORE__RUMMIKUB_H

