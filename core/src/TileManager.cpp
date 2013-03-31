#include "TileManager.h"

#include <algorithm>
#include <vector>

#include "Tile.h"

using std::random_shuffle;
using std::vector;

namespace rummikub {
namespace core {

struct TileManager::Member {
  vector<Tile> tiles;
};

TileManager::TileManager()
  : _{new Member{}}
{
  _->tiles.reserve(106);
  for (auto v = Tile::MIN_VALUE; v <= Tile::MAX_VALUE; ++v) {
    for(unsigned i=0; i<2; ++i) {
      _->tiles.push_back(Tile{RED, v});
      _->tiles.push_back(Tile{BLUE, v});
      _->tiles.push_back(Tile{YELLOW, v});
      _->tiles.push_back(Tile{BLACK, v});
    }
  }
  _->tiles.push_back(Tile::joker(RED));
  _->tiles.push_back(Tile::joker(BLACK));
}

TileManager::~TileManager()
{
  delete _;
}

Tile
TileManager::getAndRemoveTile()
{
  auto result = _->tiles.back();
  _->tiles.pop_back();
  return result;
}

bool
TileManager::empty() const
{
  return _->tiles.empty();
}

void
TileManager::shuffle()
{
  random_shuffle(_->tiles.begin(), _->tiles.end());
}

} // namespace core
} // namespace rummikub

