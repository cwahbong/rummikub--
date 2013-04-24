#include "qmodel/Table.h"

#include "model/Set.h"
#include "model/Table.h"

using std::make_shared;

namespace rummikub {
namespace qmodel {

struct Table::Member {
  const s_ptr<core::Table> sp_table;
  const s_ptr<core::Table::SetCallback> sp_insertSetCallback;
  const s_ptr<core::Table::SetCallback> sp_removeSetCallback;
};

Table::Table(core::Table* table, QObject *parent)
  : QObject{parent},
    _{new Member{
      s_ptr<core::Table>{table},
      make_shared<core::Table::SetCallback>(
        [this](const s_ptr<core::Set>& sp_set) {
          emit setInserted(make_shared<const Set>(sp_set.get()));
        }
      ),
      make_shared<core::Table::SetCallback>(
        [this](const s_ptr<core::Set>& sp_set) {
          emit setRemoved(make_shared<const Set>(sp_set.get()));
        }
      )
    }}
{
  _->sp_table->addInsertSetCallback(_->sp_insertSetCallback);
  _->sp_table->addRemoveSetCallback(_->sp_removeSetCallback);
}

Table::~Table()
{
  _->sp_table->delInsertSetCallback(_->sp_insertSetCallback);
  _->sp_table->delRemoveSetCallback(_->sp_removeSetCallback);
}

} // namespace qmodel
} // namespace rummikub

