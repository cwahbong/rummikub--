#include "PlayerImpl.h"

#include "Agent.h"

#include <utility>

using std::make_pair;

namespace rummikub {
namespace core {

void
PlayerImpl::addTile(Tile tile)
{
  if (m_tilemap.find(tile) == m_tilemap.end()) {
    m_tilemap.insert(make_pair(tile, 0));
  }
  ++m_tilemap[tile];
}

bool
PlayerImpl::removeTile(Tile tile)
{
  auto it = m_tilemap.find(tile);
  if (it == m_tilemap.end() || it->second == 0) {
    return false;
  }
  if (m_tilemap[tile]==1) {
    m_tilemap.erase(tile);
  }
  else {
    --m_tilemap[tile];
  }
  return true;
}

bool
PlayerImpl::empty()
{
  return m_tilemap.empty();
}

const map<Tile, int>&
PlayerImpl::getTiles() const
{
  return m_tilemap;
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

