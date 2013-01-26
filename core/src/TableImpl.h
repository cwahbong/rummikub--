/**
 * INTERNAL HEADER, DO NOT INCLUDE EXTERNALLY!!!
 */
#include "Table.h"

#include <memory>

using std::set;
using std::shared_ptr;
using std::vector;
using std::weak_ptr;

namespace rummikub {
namespace core {

class TableImpl : public Table {
private:
  set<shared_ptr<Set>> m_sets{};

  bool validate() const;

protected:
  TableImpl(const TableImpl&) = default;
  TableImpl& operator=(const TableImpl&) = default;

public:
  TableImpl() noexcept = default;

  shared_ptr<Table> clone() const;

  void addSet(const shared_ptr<Set>&);
  weak_ptr<Set> setRemoveConst(const shared_ptr<const Set>&);
  vector<weak_ptr<const Set>> getSets() const;
  void clean();
};

} // namespace core
} // namespace rummikub

