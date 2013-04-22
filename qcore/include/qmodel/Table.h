#ifndef RUMMIKUB_QCORE__TABLE_H
#define RUMMIKUB_QCORE__TABLE_H

#include "CoreFwd.h"
#include "StdMemory.h"
#include "model/Table.h"

// #include "qmodel/Set.h"

#include <QObject>

namespace rummikub {
namespace qmodel {

class Table : public QObject {
  Q_OBJECT

public:
  explicit Table(core::Table* table, QObject *parent = 0);
    
signals:
  // void setAdded(const cs_ptr<Set>&);
  // void setRemoved(const cs_ptr<Set>&);

private:
  const s_ptr<core::Table> m_table;
  s_ptr<core::Table::SetCallback> m_insertSetCallback;
  s_ptr<core::Table::SetCallback> m_removeSetCallback;
};

} // namespace qmodel
} // namespace rummikub

#endif // RUMMIKUB_QCORE__TABLE_H

