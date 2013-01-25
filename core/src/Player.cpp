#include "Player.h"
#include "PlayerImpl.h"

using std::shared_ptr;

namespace rummikub {
namespace core {

shared_ptr<Player>
Player::newPlayer() {
  return shared_ptr<Player>{new PlayerImpl{}};
}

} // namespace core
} // namespace rummikub

