#ifndef RUMMIKUB_QCORE__TABLE_H
#define RUMMIKUB_QCORE__TABLE_H

#include "CoreFwd.h"
#include "StdMemory.h"
#include "model/Table.h"

#include "qmodel/Set.h"

#include <QObject>

namespace rummikub {
namespace qmodel {

class Table : public QObject {
  Q_OBJECT

public:
  explicit Table(const s_ptr<core::Table>&, QObject *parent = 0);
  ~Table();
    
signals:
  void setInserted(const cs_ptr<Set>&);
  void setRemoved(const cs_ptr<Set>&);

private:
  struct Member;
  const u_ptr<Member> _;
};

} // namespace qmodel
} // namespace rummikub

#endif // RUMMIKUB_QCORE__TABLE_H

