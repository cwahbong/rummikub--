#include "Table.h"
#include "TableImpl.h"

namespace rummikub {
namespace core {

shared_ptr<Table>
Table::newTable()
{
  return shared_ptr<Table>{new TableImpl{}};
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

