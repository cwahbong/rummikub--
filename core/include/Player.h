#ifndef RUMMIKUB_CORE__PLAYER_H
#define RUMMIKUB_CORE__PLAYER_H

#include "CoreFwd.h"

namespace rummikub {
namespace core {

class Player {
public:
  virtual void addTile() = 0;
  virtual void removeTile() = 0;
};

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__PLAYER_H

