#include "Table.h"

#include "Set.h"

#include <set>

using std::const_pointer_cast;
using std::set;
using std::shared_ptr;
using std::vector;
using std::weak_ptr;

namespace rummikub {
namespace core {

struct Table::Member {
  set<shared_ptr<Set>> sets{};
  set<s_ptr<SetCallback>> insertSetCallbacks;
  set<s_ptr<SetCallback>> removeSetCallbacks;

  bool validate() const {
    for (const auto& sp_set : sets) {
      if (sp_set->getType() == Set::NONE) {
        return false;
      }
    }
    return true;
  }
};

shared_ptr<Table>
Table::newTable()
{
  return shared_ptr<Table>{new Table{}};
}

Table::Table()
  : _{new Member{}}
{}

Table::Table(const Table& table)
  : _{new Member{}}
{
  for (const auto& sp_set : table._->sets) {
    _->sets.insert(std::make_shared<Set>(*sp_set));
  }
}

Table::~Table()
{
  delete _;
}

shared_ptr<Table>
Table::clone() const
{
  return shared_ptr<Table>{new Table{*this}};
}

void
Table::addSet(const shared_ptr<const Set>& set)
{
  _->sets.insert(std::make_shared<Set>(*set));
}

void
Table::clear()
{
  _->sets.clear();
}

weak_ptr<Set>
Table::setRemoveConst(const shared_ptr<const Set>& set)
{
  auto it = _->sets.find(const_pointer_cast<Set>(set));
  if (it != _->sets.end()) {
    return weak_ptr<Set>{*it};
  }
  return weak_ptr<Set>{};
}

vector<weak_ptr<const Set>>
Table::getSets() const
{
  return vector<weak_ptr<const Set>>{_->sets.begin(), _->sets.end()};
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
Table::addInsertSetCallback(const s_ptr<SetCallback>& callback)
{
  _->insertSetCallbacks.insert(callback);
}

void
Table::addRemoveSetCallback(const s_ptr<SetCallback>& callback)
{
  _->removeSetCallbacks.insert(callback);
}

void
Table::delInsertSetCallback(const s_ptr<SetCallback>& callback)
{
  _->insertSetCallbacks.erase(callback);
}

void
Table::delRemoveSetCallback(const s_ptr<SetCallback>& callback)
{
  _->removeSetCallbacks.erase(callback);
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

} // namespace core
} // namespace rummikub

