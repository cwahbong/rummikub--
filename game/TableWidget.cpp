#include "TableWidget.h"
#include "ui_TableWidget.h"

#include "SetWidget.h"

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
  QObject::connect(this, SIGNAL(setInserted(const s_ptr<Set>&)),
                   this, SLOT(insertSet(const s_ptr<Set>&)));
  QObject::connect(this, SIGNAL(setRemoved(const s_ptr<Set>&)),
                   this, SLOT(removeSet(const s_ptr<Set>&)));
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
      emit setInserted(sp_set);
    }
  );
  m_sp_table->addInsertSetCallback(m_insertSetCallback);
  m_removeSetCallback = make_shared<Table::SetCallback>(
    [this](const s_ptr<Set>& sp_set) {
      emit setRemoved(sp_set);
    }
  );
  m_sp_table->addRemoveSetCallback(m_removeSetCallback);
}

void
TableWidget::unbindTable()
{
  if (m_sp_table) {
    m_sp_table->delInsertSetCallback(m_insertSetCallback);
    m_sp_table->delRemoveSetCallback(m_removeSetCallback);
    m_sp_table = nullptr;
  }
}

void
TableWidget::insertSet(const s_ptr<Set>& sp_set)
{
  auto* p_setWidget = new SetWidget();
  p_setWidget->bindSet(sp_set);
  layout()->addWidget(p_setWidget);
}

void
TableWidget::removeSet(const s_ptr<Set>& sp_set)
{
  // TODO
  /* for (auto* p_SetWidget : findChildren<SetWidget*>()) {
  } */
}

} // namespace game
} // namespace rummikub

