#include "qmodel/Table.h"

#include "model/Set.h"
#include "model/Table.h"

using std::make_shared;

namespace rummikub {
namespace qmodel {

Table::Table(core::Table* table, QObject *parent)
 : QObject{parent},
   m_table{table}
{
}

} // namespace qmodel
} // namespace rummikub

