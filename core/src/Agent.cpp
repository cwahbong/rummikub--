#include "Agent.h"

#include "Set.h"
#include "Table.h"
#include "Tile.h"

using std::shared_ptr;
using std::weak_ptr;

namespace rummikub {
namespace core {

bool
AgentDelegate::putTile(Tile tile, const shared_ptr<const Set>& set)
{
  auto sp_set = m_sp_table->setRemoveConst(set).lock();
  if (!sp_set) return false;
  sp_set->insert(tile);
  return true;
}

bool
AgentDelegate::moveTile(
    Tile tile,
    const shared_ptr<const Set>& from,
    const shared_ptr<const Set>& to)
{
  auto sp_f = m_sp_table->setRemoveConst(from).lock();
  auto sp_t = m_sp_table->setRemoveConst(to).lock();
  if (!sp_f || !sp_t) return false;
  if (!sp_f->remove(tile)) return false;
  sp_t->insert(tile);
  return true;
}


} // namespace core
} // namespace rummikub

