#include "PlayerImpl.h"

#include "Agent.h"

#include <utility>

using std::make_pair;

namespace rummikub {
namespace core {

shared_ptr<Player>
PlayerImpl::clone() const
{
  return shared_ptr<Player>{new PlayerImpl{*this}};
}

void
PlayerImpl::addTile(const Tile& tile, size_t count)
{
  m_holder.add(tile, count);
}

bool
PlayerImpl::removeTile(const Tile& tile, size_t count)
{
  return m_holder.remove(tile, count);
}

void
PlayerImpl::clearTiles()
{
  return m_holder.clear();
}

bool
PlayerImpl::hasTile(const Tile& tile) const
{
  return m_holder.has(tile);
}

size_t
PlayerImpl::count(const Tile& tile) const
{
  return m_holder.count(tile);
}

bool
PlayerImpl::empty() const
{
  return m_holder.empty();
}

vector<Tile>
PlayerImpl::getKinds() const
{
  return m_holder.kinds();
}

std::weak_ptr<Agent>
PlayerImpl::getAgent()
{
  return m_sp_agent;
}

void
PlayerImpl::setAgent(const shared_ptr<Agent>& sp_agent)
{
  m_sp_agent = sp_agent;
}

} // namespace core
} // namespace rummikub

