#include "model/Player.h"

#include "Holder.h"
#include "model/Tile.h"

#include <set>

using std::set;
using std::vector;

namespace rummikub {
namespace core {

struct Player::Member {
  const cw_ptr<Game> wp_game;
  Holder<Tile> holder;
};

Player::Player(const cw_ptr<Game>& wp_game)
  : _{new Member{wp_game}}
{/* Empty. */}

Player::Player(const Player& player)
  : _{new Member(*player._)}
{/* Empty. */}

Player::~Player()
{
  delete _;
}

void
Player::addTile(const Tile& tile, size_t count)
{
  _->holder.add(tile, count);
}

bool
Player::removeTile(const Tile& tile, size_t count)
{
  return _->holder.remove(tile, count);
}

void
Player::clearTiles()
{
  _->holder.clear();
}

bool
Player::hasTile(const Tile& tile) const
{
  return _->holder.has(tile);
}

size_t
Player::count(const Tile& tile) const
{
  return _->holder.count(tile);
}

bool
Player::empty() const
{
  return _->holder.empty();
}

vector<Tile>
Player::getKinds() const
{
  return _->holder.kinds();
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

