#include "Agent.h"

#include "EventReceiver.h"
#include "model/Hand.h"
#include "model/Set.h"
#include "model/Table.h"
#include "model/Tile.h"

using std::make_shared;
using std::const_pointer_cast;

namespace rummikub {

struct Agent::Delegate::Member {
  const w_ptr<EventReceiver> wp_eventReceiver;
  const cs_ptr<Table> csp_oldTable;
  const cs_ptr<Hand> csp_oldHand;
  const s_ptr<Table> sp_table;
  const s_ptr<Hand> sp_player;
  size_t put;
};

Agent::Delegate::Delegate(const w_ptr<EventReceiver>& wp_eventReceiver,
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

Agent::Delegate::~Delegate()
{/* Empty. */}

bool
Agent::Delegate::putTile(Tile tile, const cs_ptr<Set>& sp_set)
{
  if (!_->sp_player->hasTile(tile)) return false;
  const auto& sp_newSet = const_pointer_cast<Set>(sp_set ? sp_set : _->sp_table->addSet());
  sp_newSet->insert(tile);
  _->wp_eventReceiver.lock()->tilePut(_->sp_player, tile, sp_set);
  _->sp_player->removeTile(tile);
  ++_->put;
  return true;
}

bool
Agent::Delegate::moveTile(
    Tile tile,
    const cs_ptr<Set>& sp_from,
    const cs_ptr<Set>& sp_to)
{
  if (!sp_from || !sp_to) return false;
  if (!const_pointer_cast<Set>(sp_from)->remove(tile)) return false;
  _->sp_table->clean();
  const_pointer_cast<Set>(sp_to)->insert(tile);
  _->wp_eventReceiver.lock()->tileMoved(tile, sp_from, sp_to);
  return true;
}

const cs_ptr<Table>
Agent::Delegate::getTable() const
{
  return _->sp_table;
}

const cs_ptr<Hand>
Agent::Delegate::getHand() const
{
  return _->sp_player;
}

size_t
Agent::Delegate::countPut() const
{
  return _->put;
}

bool
Agent::Delegate::validate() const
{
  for (const auto& wp_set : _->sp_table->getSets()) {
    if (wp_set.lock()->getType() == Set::NONE) {
      return false;
    }
  }
  return true;
}

void
Agent::Delegate::restore()
{
  *_->sp_table = *_->csp_oldTable;
  *_->sp_player = *_->csp_oldHand;
  _->put = 0;
  _->wp_eventReceiver.lock()->restored(_->sp_table, _->sp_player);
}

} // namespace rummikub

