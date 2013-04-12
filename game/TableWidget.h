#ifndef RUMMIKUB_GAME__TABLEWIDGET_H
#define RUMMIKUB_GAME__TABLEWIDGET_H

#include "CoreFwd.h"
#include "StdMemory.h"
#include "Table.h"

#include <QWidget>

namespace Ui {
class TableWidget;
} // namespace Ui

namespace rummikub {
namespace game {

class TableWidget : public QWidget
{
  Q_OBJECT
    
public:
  explicit TableWidget(QWidget *parent = 0);
  ~TableWidget();
  void bindTable(const s_ptr<core::Table>&);
  void unbindTable();
    
private:
  Ui::TableWidget *ui;
  s_ptr<core::Table> m_sp_table;
  s_ptr<core::Table::SetCallback> m_insertSetCallback;
  s_ptr<core::Table::SetCallback> m_removeSetCallback;
};

} // namespace game
} // namespace rummikub

#endif // RUMMIKUB_GAME__TABLEWIDGET_H

