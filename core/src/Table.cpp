#include "model/Table.h"

#include "model/Set.h"

#include <set>

using std::const_pointer_cast;
using std::make_shared;
using std::set;
using std::shared_ptr;
using std::vector;
using std::weak_ptr;

namespace rummikub {

struct Table::Member {
  set<shared_ptr<Set>> sets;

  bool validate() const {
    for (const auto& sp_set : sets) {
      if (sp_set->getType() == Set::NONE) {
        return false;
      }
    }
    return true;
  }
};

Table::Table()
  : _{new Member{}}
{/* Empty. */}

Table::Table(const Table& table)
  : _{new Member(*table._)}
{
  for (const auto& sp_set : table._->sets) {
    _->sets.insert(std::make_shared<Set>(*sp_set));
  }
}

Table::~Table()
{/* Empty. */}

s_ptr<Set>
Table::addSet()
{
  const auto& sp_set = make_shared<Set>();
  _->sets.insert(sp_set);
  return sp_set;
}

s_ptr<Set>
Table::addSet(const cs_ptr<Set>& sp_set)
{
  const auto& sp_newSet = make_shared<Set>(*sp_set);
  _->sets.insert(sp_newSet);
  return sp_newSet;
}

void
Table::clear()
{
  _->sets.clear();
}

vector<cw_ptr<Set>>
Table::getSets() const
{
  return vector<cw_ptr<Set>>{_->sets.begin(), _->sets.end()};
}

void
Table::clean()
{
  for (auto it = _->sets.cbegin(); it != _->sets.cend(); ) {
    if ((*it)->empty()) {
      _->sets.erase(it++);
    }
    else {
      ++it;
    }
  }
}

void
copyTiles(const std::shared_ptr<Table>& to,
          const std::shared_ptr<const Table>& from)
{
  to->clear();
  for (const auto& wp_set : from->getSets()) {
    to->addSet(wp_set.lock());
  }
}

} // namespace rummikub

