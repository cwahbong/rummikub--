#include "model/Player.h"

#include "Holder.h"
#include "model/Tile.h"

#include <set>

using std::set;
using std::vector;

namespace rummikub {
namespace core {

struct Player::Member {
  s_ptr<Agent> sp_agent{};
  Holder<Tile> holder{};
  set<s_ptr<TileCallback>> insertTileCallbacks;
  set<s_ptr<TileCallback>> removeTileCallbacks;

  void
  insertTileCall(const Tile& tile)
  {
    for (const auto& sp_callback : insertTileCallbacks) {
      (*sp_callback)(tile);
    }
  }

  void
  removeTileCall(const Tile& tile)
  {
    for (const auto& sp_callback : removeTileCallbacks) {
      (*sp_callback)(tile);
    }
  }
};

s_ptr<Player>
Player::newPlayer() {
  return s_ptr<Player>{new Player{}};
}

s_ptr<Player>
Player::clone() const
{
  return s_ptr<Player>{new Player{*this}};
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
  _->insertTileCall(tile);
}

bool
Player::removeTile(const Tile& tile, size_t count)
{
  bool result = _->holder.remove(tile, count);
  if (result) {
    _->removeTileCall(tile);
  }
  return result;
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

std::weak_ptr<Agent>
Player::getAgent()
{
  return _->sp_agent;
}

void
Player::setAgent(const s_ptr<Agent>& sp_agent)
{
  _->sp_agent = sp_agent;
}
void
Player::addInsertTileCallback(const s_ptr<TileCallback>& callback)
{
  _->insertTileCallbacks.insert(callback);
}

void
Player::addRemoveTileCallback(const s_ptr<TileCallback>& callback)
{
  _->removeTileCallbacks.insert(callback);
}

void
Player::delInsertTileCallback(const s_ptr<TileCallback>& callback)
{
  _->insertTileCallbacks.erase(callback);
}

void
Player::delRemoveTileCallback(const s_ptr<TileCallback>& callback)
{
  _->removeTileCallbacks.erase(callback);
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

