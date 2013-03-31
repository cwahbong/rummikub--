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

public:
  TileManager();
  virtual ~TileManager();

  Tile getAndRemoveTile();
  bool empty() const;

  void shuffle();

private:
  struct Member;
  Member* _;
};

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__TILE_MANAGER_H

