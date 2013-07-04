#ifndef RUMMIKUB_CORE__RUMMIKUB_H
#define RUMMIKUB_CORE__RUMMIKUB_H

#include "CoreFwd.h"

#include "StdMemory.h"
#include "Util.h"

#include <vector>

namespace rummikub {
namespace core {

class Rummikub {
public:
  Rummikub(const w_ptr<EventReceiver>&, const std::vector<s_ptr<Agent>>&);
  ~Rummikub();

  void startGame();

private:
  struct Member;
  const u_ptr<Member> _;
};

} // namespace core
} // namespace rmmikub

#endif // RUMMIKUB_CORE__RUMMIKUB_H

