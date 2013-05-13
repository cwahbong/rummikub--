#include "AgentDelegate.h"

#include "EventReceiver.h"
#include "Game.h"
#include "model/Player.h"
#include "model/Set.h"
#include "model/Table.h"
#include "model/Tile.h"

using std::make_shared;

namespace rummikub {
namespace core {

struct AgentDelegate::Member {
  const cw_ptr<Game> wp_game;
  const cs_ptr<Table> csp_oldTable;
  const cs_ptr<Player> csp_oldPlayer;
  const s_ptr<Table> sp_table;
  const s_ptr<Player> sp_player;
  size_t put;
};

AgentDelegate::AgentDelegate(const cw_ptr<Game>& wp_game,
                             const s_ptr<Table>& sp_table,
                             const s_ptr<Player>& sp_player)
  : _{new Member{
        wp_game,
        make_shared<Table>(*sp_table),
        make_shared<Player>(*sp_player),
        sp_table,
        sp_player,
        0
    }}
{/* Empty. */}

AgentDelegate::~AgentDelegate()
{/* Empty. */}

bool
AgentDelegate::putTile(Tile tile, const cs_ptr<Set>& set)
{
  if (!_->sp_player->hasTile(tile)) return false;
  s_ptr<Set> sp_set;
  if (set) {
    sp_set = _->sp_table->setRemoveConst(set).lock();
    sp_set->insert(tile);
  } else {
    const auto& sp_set = _->sp_table->addSet();
    sp_set->insert(tile);
  }
  _->sp_player->removeTile(tile);
  ++_->put;
  _->wp_game.lock()->getEventReceiver()->tilePut(_->sp_player, tile, set);
  return true;
}

bool
AgentDelegate::moveTile(
    Tile tile,
    const cs_ptr<Set>& from,
    const cs_ptr<Set>& to)
{
  auto sp_f = _->sp_table->setRemoveConst(from).lock();
  auto sp_t = _->sp_table->setRemoveConst(to).lock();
  if (!sp_f || !sp_t) return false;
  if (!sp_f->remove(tile)) return false;
  _->sp_table->clean();
  sp_t->insert(tile);
  _->wp_game.lock()->getEventReceiver()->tileMoved(tile, from, to);
  return true;
}

const cs_ptr<Table>
AgentDelegate::getTable() const
{
  return _->sp_table;
}

const cs_ptr<Player>
AgentDelegate::getPlayer() const
{
  return _->sp_player;
}

size_t
AgentDelegate::countPut() const
{
  return _->put;
}

bool
AgentDelegate::validate() const
{
  for (const auto& wp_set : _->sp_table->getSets()) {
    if (wp_set.lock()->getType() == Set::NONE) {
      return false;
    }
  }
  return true;
}

void
AgentDelegate::restore()
{
  copyTiles(_->sp_table, _->csp_oldTable);
  copyTiles(_->sp_player, _->csp_oldPlayer);
  _->put = 0;
  _->wp_game.lock()->getEventReceiver()->restored(_->sp_table, _->sp_player);
}

} // namespace core
} // namespace rummikub

