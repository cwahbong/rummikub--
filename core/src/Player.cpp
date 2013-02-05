#include "Player.h"
#include "PlayerImpl.h"

using std::shared_ptr;

namespace rummikub {
namespace core {

shared_ptr<Player>
Player::newPlayer() {
  return shared_ptr<Player>{new PlayerImpl{}};
}

void
copyTiles(const std::shared_ptr<Player>& to,
          const std::shared_ptr<const Player>& from)
{
  to->clearTiles();
  for (const auto& tile : from->getKinds()) {
    to->addTile(tile, from->count(tile));
  }
}

} // namespace core
} // namespace rummikub

