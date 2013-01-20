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
  TableImpl(const TableImpl&) = delete;
  TableImpl& operator=(const TableImpl&) = delete;

private:
  set<shared_ptr<Set>> m_sets{};

  bool validate() const;

public:
  TableImpl() noexcept = default;

  void addSet(const shared_ptr<Set>&);
  weak_ptr<Set> setRemoveConst(const shared_ptr<const Set>&);
  vector<weak_ptr<const Set>> getSets() const;
  void clean();
};

} // namespace core
} // namespace rummikub

