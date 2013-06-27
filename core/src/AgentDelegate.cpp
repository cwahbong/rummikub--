#include "AgentDelegate.h"

#include "EventReceiver.h"
#include "model/Hand.h"
#include "model/Set.h"
#include "model/Table.h"
#include "model/Tile.h"

using std::make_shared;

namespace rummikub {
namespace core {

struct AgentDelegate::Member {
  const w_ptr<EventReceiver> wp_eventReceiver;
  const cs_ptr<Table> csp_oldTable;
  const cs_ptr<Hand> csp_oldHand;
  const s_ptr<Table> sp_table;
  const s_ptr<Hand> sp_player;
  size_t put;
};

AgentDelegate::AgentDelegate(const w_ptr<EventReceiver>& wp_eventReceiver,
                             const s_ptr<Table>& sp_table,
                             const s_ptr<Hand>& sp_player)
  : _{new Member{
        wp_eventReceiver,
        make_shared<Table>(*sp_table),
        make_shared<Hand>(*sp_player),
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
  _->wp_eventReceiver.lock()->tilePut(_->sp_player, tile, set);
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
  _->wp_eventReceiver.lock()->tileMoved(tile, from, to);
  return true;
}

const cs_ptr<Table>
AgentDelegate::getTable() const
{
  return _->sp_table;
}

const cs_ptr<Hand>
AgentDelegate::getHand() const
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
  copyTiles(_->sp_player, _->csp_oldHand);
  _->put = 0;
  _->wp_eventReceiver.lock()->restored(_->sp_table, _->sp_player);
}

} // namespace core
} // namespace rummikub

