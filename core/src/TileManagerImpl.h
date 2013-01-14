/**
 * INTERNAL HEADER, DO NOT INCLUDE EXTERNALLY!!!
 */
#include "TileManager.h"

#include <memory>
#include <vector>

using std::unique_ptr;
using std::vector;

namespace rummikub {
namespace core {

class TileManagerImpl : public TileManager {
private:
  TileManagerImpl(const TileManagerImpl&) = delete;
  TileManagerImpl& operator=(const TileManagerImpl&) = delete;

private:
  unique_ptr<vector<Tile>> m_up_tiles;

public:
  TileManagerImpl();
  TileManagerImpl(TileManagerImpl&&);

  Tile getAndRemoveTile();

  static TileManagerImpl* newShuffledTiles();
};

} // namespace core
} // namespace rummikub

