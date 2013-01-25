#include "PlayerImpl.h"

#include "Agent.h"

namespace rummikub {
namespace core {

void
PlayerImpl::addTile(Tile tile)
{
}

bool
PlayerImpl::removeTile(Tile tile)
{
}



bool
PlayerImpl::empty()
{
  return m_tiles.empty();
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

