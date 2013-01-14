#include "TileManager.h"

#include "TileManagerImpl.h"

namespace rummikub {
namespace core {

TileManager*
TileManager::newShuffledTiles()
{
  return TileManagerImpl::newShuffledTiles();
}

} // namespace core
} // namespace rummikub

