#include "TileManagerImpl.h"

#include "Tile.h"

#include <algorithm>

using std::move;
using std::random_shuffle;

namespace rummikub {
namespace core {

TileManagerImpl::TileManagerImpl()
  : m_up_tiles(new vector<Tile>{})
{
  auto& tiles = *m_up_tiles;
  tiles.reserve(106);
  for (auto v = Tile::MIN_VALUE; v<Tile::MAX_VALUE; ++v) {
    tiles.push_back(Tile{Tile::RED, v});
    tiles.push_back(Tile{Tile::BLUE, v});
    tiles.push_back(Tile{Tile::YELLOW, v});
    tiles.push_back(Tile{Tile::BLACK, v});
  }
  tiles.push_back(Tile::joker(Tile::RED));
  tiles.push_back(Tile::joker(Tile::BLACK));
}

TileManagerImpl::TileManagerImpl(TileManagerImpl&& tileManager)
  : m_up_tiles(move(tileManager.m_up_tiles))
{/* Empty. */}

Tile
TileManagerImpl::getAndRemoveTile()
{
  auto&& result = m_up_tiles->back();
  m_up_tiles->pop_back();
  return move(result);
}

TileManagerImpl*
TileManagerImpl::newShuffledTiles()
{
  TileManagerImpl* result = new TileManagerImpl{};
  auto& tiles = *result->m_up_tiles;
  random_shuffle(tiles.begin(), tiles.end());
  return result;
}

} // namespace core
} // namespace rummikub

