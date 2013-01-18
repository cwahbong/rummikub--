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
  vector<weak_ptr<Set>> getSets();
  void clean();
};

} // namespace core
} // namespace rummikub

