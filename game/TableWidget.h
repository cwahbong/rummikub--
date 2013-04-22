#ifndef RUMMIKUB_GAME__TABLEWIDGET_H
#define RUMMIKUB_GAME__TABLEWIDGET_H

#include "CoreFwd.h"
#include "StdMemory.h"
#include "model/Table.h"

#include <QWidget>

namespace Ui {
class TableWidget;
} // namespace Ui

namespace rummikub {
namespace game {

class TableWidget : public QWidget
{
  Q_OBJECT
  using Set = core::Set;
    
public:
  explicit TableWidget(QWidget *parent = 0);
  ~TableWidget();
  void bindTable(const s_ptr<core::Table>&);
  void unbindTable();

signals:
  void setInserted(const s_ptr<Set>&);
  void setRemoved(const s_ptr<Set>&);

private slots:
  void insertSet(const s_ptr<Set>&);
  void removeSet(const s_ptr<Set>&);
    
private:
  Ui::TableWidget *ui;
  s_ptr<core::Table> m_sp_table;
  s_ptr<core::Table::SetCallback> m_insertSetCallback;
  s_ptr<core::Table::SetCallback> m_removeSetCallback;
};

} // namespace game
} // namespace rummikub

#endif // RUMMIKUB_GAME__TABLEWIDGET_H

