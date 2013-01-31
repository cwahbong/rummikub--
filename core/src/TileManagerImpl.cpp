#include "TileManagerImpl.h"

#include "Tile.h"

#include <algorithm>

using std::make_shared;
using std::move;
using std::random_shuffle;

namespace rummikub {
namespace core {

TileManagerImpl::TileManagerImpl()
  : m_tiles()
{
  m_tiles.reserve(106);
  for (auto v = Tile::MIN_VALUE; v <= Tile::MAX_VALUE; ++v) {
    for(unsigned i=0; i<2; ++i) {
      m_tiles.push_back(Tile{RED, v});
      m_tiles.push_back(Tile{BLUE, v});
      m_tiles.push_back(Tile{YELLOW, v});
      m_tiles.push_back(Tile{BLACK, v});
    }
  }
  m_tiles.push_back(Tile::joker(RED));
  m_tiles.push_back(Tile::joker(BLACK));
}

TileManagerImpl::TileManagerImpl(TileManagerImpl&& tileManager)
  : m_tiles(move(tileManager.m_tiles))
{/* Empty. */}

Tile
TileManagerImpl::getAndRemoveTile()
{
  auto result = m_tiles.back();
  m_tiles.pop_back();
  return result;
}

bool
TileManagerImpl::empty()
{
  return m_tiles.empty();
}

shared_ptr<TileManagerImpl>
TileManagerImpl::newShuffledTiles()
{
  auto result = make_shared<TileManagerImpl>();
  random_shuffle(result->m_tiles.begin(), result->m_tiles.end());
  return result;
}

} // namespace core
} // namespace rummikub

