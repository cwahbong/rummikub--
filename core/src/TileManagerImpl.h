/**
 * INTERNAL HEADER, DO NOT INCLUDE EXTERNALLY!!!
 */
#include "TileManager.h"

#include <vector>

using std::shared_ptr;
using std::vector;

namespace rummikub {
namespace core {

class TileManagerImpl : public TileManager {
private:
  TileManagerImpl(const TileManagerImpl&) = delete;
  TileManagerImpl& operator=(const TileManagerImpl&) = delete;

private:
  vector<Tile> m_tiles;

public:
  TileManagerImpl();
  TileManagerImpl(TileManagerImpl&&);

  Tile getAndRemoveTile();

  static shared_ptr<TileManagerImpl> newShuffledTiles();
};

} // namespace core
} // namespace rummikub

