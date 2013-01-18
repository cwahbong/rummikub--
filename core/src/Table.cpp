#include "Table.h"
#include "TableImpl.h"

namespace rummikub {
namespace core {

shared_ptr<Table>
Table::newTable()
{
  return shared_ptr<Table>{new TableImpl{}};
}

} // namespace core
} // namespace rummikub

