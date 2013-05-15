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
  Rummikub(const cw_ptr<Game>&, const std::vector<s_ptr<Agent>>&);
  ~Rummikub();

  void startGame();

private:
  struct Member;
  Member* _;
};

} // namespace core
} // namespace rmmikub

#endif // RUMMIKUB_CORE__RUMMIKUB_H

