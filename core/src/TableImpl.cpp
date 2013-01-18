#include "TableImpl.h"

#include "Set.h"

namespace rummikub {
namespace core {

bool
TableImpl::validate() const
{
  for (const auto& sp_set : m_sets) {
    if (sp_set->getType() == Set::NONE) {
      return false;
    }
  }
  return true;
}

void
TableImpl::addSet(const shared_ptr<Set>& set)
{
  m_sets.insert(set);
}

vector<weak_ptr<Set>>
TableImpl::getSets()
{
  return vector<weak_ptr<Set>>{m_sets.begin(), m_sets.end()};
}

void
TableImpl::clean()
{
  for (auto it = m_sets.cbegin(); it != m_sets.cend(); ) {
    if ((*it)->empty()) {
      m_sets.erase(it++);
    }
    else {
      ++it;
    }
  }
}

} // namespace core
} // namespace rummikub

