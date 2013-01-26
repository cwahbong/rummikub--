#include "Agent.h"

#include "Player.h"
#include "Set.h"
#include "Table.h"
#include "Tile.h"

using std::shared_ptr;
using std::weak_ptr;

namespace rummikub {
namespace core {

AgentDelegate::AgentDelegate(const std::shared_ptr<Table>& sp_table,
                             const std::shared_ptr<Player>& sp_player)
  : m_sp_oldTable{sp_table},
    m_sp_oldPlayer{sp_player},
    m_sp_table{sp_table->clone()},
    m_sp_player{sp_player->clone()}
{/* Empty. */}

bool
AgentDelegate::putTile(Tile tile, const shared_ptr<const Set>& set) const
{
  shared_ptr<Set> sp_set;
  if (set) {
    sp_set = m_sp_table->setRemoveConst(set).lock();
  } else {
    sp_set = Set::newSet();
    m_sp_table->addSet(sp_set);
  }
  const auto& tilesMap = m_sp_player->getTiles();
  if (!sp_set || tilesMap.find(tile) == tilesMap.end()) return false;
  m_sp_player->removeTile(tile);
  sp_set->insert(tile);
  return true;
}

bool
AgentDelegate::moveTile(
    Tile tile,
    const shared_ptr<const Set>& from,
    const shared_ptr<const Set>& to) const
{
  auto sp_f = m_sp_table->setRemoveConst(from).lock();
  auto sp_t = m_sp_table->setRemoveConst(to).lock();
  if (!sp_f || !sp_t) return false;
  if (!sp_f->remove(tile)) return false;
  sp_t->insert(tile);
  return true;
}

const Table&
AgentDelegate::getTable() const
{
  return *m_sp_table;
}

const Player&
AgentDelegate::getPlayer() const
{
  return *m_sp_player;
}

bool
AgentDelegate::validate() const
{
  // TODO implement
}

void
AgentDelegate::restore() const
{
  // TODO implement
}

} // namespace core
} // namespace rummikub

