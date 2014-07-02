#include "TableWidget.h"
#include "ui_TableWidget.h"

#include "SetWidget.h"

#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>

#include <QDebug>

namespace rummikub {
namespace game {

TableWidget::TableWidget(QWidget *parent)
  : QWidget(parent),
    ui(new Ui::TableWidget)
{
  ui->setupUi(this);
  ui->newSetLabel->setVisible(false);
}

TableWidget::~TableWidget()
{
  delete ui;
}

void
TableWidget::putTile(
    const Tile& tile,
    const cs_ptr<Set>& sp_set)
{
  if (_setMap.find(sp_set) == _setMap.end()) {
    insertSet(sp_set);
  }
  else {
    _setMap[sp_set]->insertTile(tile);
  }
}

void
TableWidget::moveTile(
    const Tile& tile,
    const cs_ptr<Set>& sp_set_from,
    const cs_ptr<Set>& sp_set_to)
{
  qDebug() << "TableWidget moveTile" << sp_set_from.get() << sp_set_to.get();
  if (_setMap.find(sp_set_to) == _setMap.end()) {
    insertSet(sp_set_to);
  } else {
    _setMap[sp_set_to]->insertTile(tile);
  }
  _setMap[sp_set_from]->removeTile(tile);
}

void
TableWidget::restore(const cs_ptr<Table>& sp_table)
{
  for (auto* p_setWidget : findChildren<SetWidget*>()) {
    delete p_setWidget;
  }
  for (const auto& cw_set : sp_table->getSets()) {
    insertSet(cw_set.lock());
  }
}

void
TableWidget::insertSet(const cs_ptr<Set>& sp_set)
{
  auto* p_setWidget = new SetWidget();
  _setMap[sp_set] = p_setWidget;
  p_setWidget->setSet(sp_set);
  ui->setsLayout->addWidget(p_setWidget);
  connect(p_setWidget, &SetWidget::chosen,
          this, &TableWidget::onSetChosen);
  connect(p_setWidget, &SetWidget::tileChosen,
          this, &TableWidget::onTileChosen);
}

void
TableWidget::animateMoveTile(
    const cs_ptr<Set>& sp_from,
    const cs_ptr<Set>& sp_to,
    const Tile&)
{
  // TODO
}

void
TableWidget::animateTo(const cs_ptr<Table>& sp_table)
{
  // TODO
}

void
TableWidget::dragEnterEvent(QDragEnterEvent* event)
{
  ui->newSetLabel->setVisible(true);
  event->accept();
}

void
TableWidget::dragLeaveEvent(QDragLeaveEvent* event)
{
  ui->newSetLabel->setVisible(false);
  event->accept();
}

void
TableWidget::dropEvent(QDropEvent* event)
{
  ui->newSetLabel->setVisible(false);
  event->accept();
  emit setChosen(nullptr);
}

void
TableWidget::onSetChosen()
{
  auto* p_setWidget = qobject_cast<SetWidget*>(sender());
  if (p_setWidget) {
    qDebug() << "TableWidget emit set Chosen";
    emit setChosen(p_setWidget);
  }
}

void
TableWidget::onTileChosen(TileWidget* p_tileWidget)
{
  auto* p_setWidget = qobject_cast<SetWidget*>(sender());
  if (p_setWidget) {
    emit tileChosen(p_tileWidget, p_setWidget);
  }
}

} // namespace game
} // namespace rummikub

