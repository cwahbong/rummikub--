#include "model/Hand.h"

#include "Holder.h"
#include "model/Tile.h"

#include <set>

using std::set;
using std::vector;

namespace rummikub {

struct Hand::Member {
  Holder<Tile> holder;
};

Hand::Hand()
  : _{new Member{}}
{/* Empty. */}

Hand::Hand(const Hand& player)
  : _{new Member(*player._)}
{/* Empty. */}

Hand::~Hand()
{/* Empty. */}

void
Hand::addTile(const Tile& tile, size_t count)
{
  _->holder.add(tile, count);
}

bool
Hand::removeTile(const Tile& tile, size_t count)
{
  return _->holder.remove(tile, count);
}

void
Hand::clearTiles()
{
  _->holder.clear();
}

bool
Hand::hasTile(const Tile& tile) const
{
  return _->holder.has(tile);
}

size_t
Hand::count(const Tile& tile) const
{
  return _->holder.count(tile);
}

bool
Hand::empty() const
{
  return _->holder.empty();
}

vector<Tile>
Hand::getKinds() const
{
  return _->holder.kinds();
}

void
copyTiles(const std::shared_ptr<Hand>& to,
          const std::shared_ptr<const Hand>& from)
{
  to->clearTiles();
  for (const auto& tile : from->getKinds()) {
    to->addTile(tile, from->count(tile));
  }
}

} // namespace rummikub

