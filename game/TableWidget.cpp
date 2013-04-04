#include "TableWidget.h"
#include "ui_TableWidget.h"

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

} // namespace game
} // namespace rummikub

