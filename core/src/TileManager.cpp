#include "TileManager.h"
#include "TileManagerImpl.h"

namespace rummikub {
namespace core {

shared_ptr<TileManager>
TileManager::newShuffledTiles()
{
  return TileManagerImpl::newShuffledTiles();
}

} // namespace core
} // namespace rummikub

