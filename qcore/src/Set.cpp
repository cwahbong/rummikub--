#include "qmodel/Set.h"

using std::make_shared;

namespace rummikub {
namespace qmodel {

struct Set::Member {
  const s_ptr<core::Set> sp_set;
  const s_ptr<core::Set::TileCallback> sp_insertTileCallback;
  const s_ptr<core::Set::TileCallback> sp_removeTileCallback;
};

Set::Set(core::Set* set, QObject *parent)
  : QObject{parent},
    _{new Member{
      s_ptr<core::Set>{set},
      make_shared<core::Set::TileCallback>(
        [this](const core::Tile& tile) {
          emit tileInserted(tile);
        }
      ),
      make_shared<core::Set::TileCallback>(
        [this](const core::Tile& tile) {
          emit tileRemoved(tile);
        }
      )
    }}
{
  _->sp_set->addInsertTileCallback(_->sp_insertTileCallback);
  _->sp_set->addRemoveTileCallback(_->sp_removeTileCallback);
}

Set::~Set()
{
  _->sp_set->delInsertTileCallback(_->sp_insertTileCallback);
  _->sp_set->delRemoveTileCallback(_->sp_removeTileCallback);
}

std::vector<core::Tile>
Set::getValidatedTiles() const
{
  return _->sp_set->getValidatedTiles();
}

} // namespace qmodel
} // namespace rummikub

