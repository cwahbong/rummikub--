#include "TableWidget.h"
#include "ui_TableWidget.h"

using rummikub::core::Set;
using rummikub::core::Table;

using std::make_shared;

namespace rummikub {
namespace game {

TableWidget::TableWidget(QWidget *parent)
  : QWidget(parent),
    ui(new Ui::TableWidget)
{
  ui->setupUi(this);
}

TableWidget::~TableWidget()
{
  unbindTable();
  delete ui;
}

void
TableWidget::bindTable(const s_ptr<Table>& sp_table)
{
  m_sp_table = sp_table;
  m_insertSetCallback = make_shared<Table::SetCallback>(
    [this](const s_ptr<Set>& sp_set) {
      // TODO add set widget
    }
  );
  m_sp_table->addInsertSetCallback(m_insertSetCallback);
  m_removeSetCallback = make_shared<Table::SetCallback>(
    [this](const s_ptr<Set>& sp_set) {
      // TODO remove set widget
    }
  );
  m_sp_table->addRemoveSetCallback(m_removeSetCallback);
}

void
TableWidget::unbindTable()
{
  m_sp_table->delInsertSetCallback(m_insertSetCallback);
  m_sp_table->delRemoveSetCallback(m_removeSetCallback);
}

} // namespace game
} // namespace rummikub

