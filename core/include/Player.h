#ifndef RUMMIKUB_CORE__PLAYER_H
#define RUMMIKUB_CORE__PLAYER_H

#include "CoreFwd.h"

#include <memory>

namespace rummikub {
namespace core {

class Player {
public:
  virtual void addTile() = 0;
  virtual void removeTile() = 0;
  virtual std::weak_ptr<Agent> getAgent() = 0;
};

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__PLAYER_H

