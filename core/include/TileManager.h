#ifndef RUMMIKUB_CORE__TILE_MANAGER_H
#define RUMMIKUB_CORE__TILE_MANAGER_H

#include "CoreFwd.h"

#include <memory>

namespace rummikub {
namespace core {

class TileManager {
private:
  TileManager(const TileManager&) = delete;
  TileManager& operator=(const TileManager&) = delete;

protected:
  TileManager() = default;

public:
  static std::shared_ptr<TileManager> newShuffledTiles();

  virtual ~TileManager() = default;
  virtual Tile getAndRemoveTile() = 0;
};

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__TILE_MANAGER_H

