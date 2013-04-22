#include "model/Player.h"

#include "model/Tile.h"

#include <vector>

using std::shared_ptr;
using std::vector;

namespace rummikub {
namespace core {

struct Player::Member {
  shared_ptr<Agent> sp_agent{};
  Holder<Tile> holder{};
};

shared_ptr<Player>
Player::newPlayer() {
  return shared_ptr<Player>{new Player{}};
}

shared_ptr<Player>
Player::clone() const
{
  return shared_ptr<Player>{new Player{*this}};
}

Player::Player()
  : _{new Member{}}
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
  return _->holder.clear();
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

std::weak_ptr<Agent>
Player::getAgent()
{
  return _->sp_agent;
}

void
Player::setAgent(const shared_ptr<Agent>& sp_agent)
{
  _->sp_agent = sp_agent;
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

