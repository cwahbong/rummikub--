#include "qmodel/Player.h"

#include "model/Player.h"
#include "model/Set.h"
#include "model/Tile.h"

using std::make_shared;

namespace rummikub {
namespace qmodel {

struct Player::Member {
  const s_ptr<core::Player> sp_player;
  const s_ptr<core::Player::TileCallback> sp_insertTileCallback;
  const s_ptr<core::Player::TileCallback> sp_removeTileCallback;
};

Player::Player(core::Player* player, QObject *parent)
  : QObject{parent},
    _{new Member{
      s_ptr<core::Player>{player},
      make_shared<core::Player::TileCallback>(
        [this](const Tile& tile) {
          emit tileInserted(tile);
        }
      ),
      make_shared<core::Player::TileCallback>(
        [this](const Tile& tile) {
          emit tileRemoved(tile);
        }
      )
    }}
{
  _->sp_player->addInsertTileCallback(_->sp_insertTileCallback);
  _->sp_player->addRemoveTileCallback(_->sp_removeTileCallback);
}

Player::~Player()
{
  _->sp_player->delInsertTileCallback(_->sp_insertTileCallback);
  _->sp_player->delRemoveTileCallback(_->sp_removeTileCallback);
}

} // namespace qmodel
} // namespace rummikub

