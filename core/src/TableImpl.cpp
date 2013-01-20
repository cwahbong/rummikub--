#include "TableImpl.h"

#include "Set.h"

using std::const_pointer_cast;

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

weak_ptr<Set>
TableImpl::setRemoveConst(const shared_ptr<const Set>& set)
{
  auto it = m_sets.find(const_pointer_cast<Set>(set));
  if (it != m_sets.end()) {
    return weak_ptr<Set>{*it};
  }
  return weak_ptr<Set>{};
}

vector<weak_ptr<const Set>>
TableImpl::getSets() const
{
  return vector<weak_ptr<const Set>>{m_sets.begin(), m_sets.end()};
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

