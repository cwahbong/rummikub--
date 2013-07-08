#include "TableWidget.h"
#include "ui_TableWidget.h"

#include "SetWidget.h"

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
  delete ui;
}

/*
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
  for (auto* p_SetWidget : findChildren<SetWidget*>()) {
  }
}
*/

} // namespace game
} // namespace rummikub

