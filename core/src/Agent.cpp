#include "Agent.h"

#include "Player.h"
#include "Set.h"
#include "Table.h"
#include "Tile.h"

namespace rummikub {
namespace core {

struct AgentDelegate::Member {
  const cs_ptr<Table> csp_oldTable;
  const cs_ptr<Player> csp_oldPlayer;
  const s_ptr<Table> sp_table;
  const s_ptr<Player> sp_player;
  size_t put;
};

AgentDelegate::AgentDelegate(const s_ptr<Table>& sp_table,
                             const s_ptr<Player>& sp_player)
  : _{new Member{
    sp_table->clone(),
    sp_player->clone(),
    sp_table,
    sp_player,
    0
  }}
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
    sp_set = std::make_shared<Set>();
    sp_set->insert(tile);
    _->sp_table->addSet(sp_set);
  }
  _->sp_player->removeTile(tile);
  ++_->put;
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
}

} // namespace core
} // namespace rummikub

