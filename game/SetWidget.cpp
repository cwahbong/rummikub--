#include "SetWidget.h"
#include "ui_SetWidget.h"

#include "TileWidget.h"

#include "model/Tile.h"
#include "model/Set.h"

#include <QDebug>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>

using std::make_shared;

namespace rummikub {
namespace game {

SetWidget::SetWidget(QWidget *parent)
  : QWidget(parent),
    ui(new Ui::SetWidget)
{
  ui->setupUi(this);
  ui->addLabel->setVisible(false);
}

SetWidget::~SetWidget()
{
  delete ui;
}

void
SetWidget::setSet(const cs_ptr<Set>& sp_set)
{
  _sp_set = sp_set;
  for (auto* p_tileWidget : findChildren<TileWidget*>()) {
    delete p_tileWidget;
  }
  for (const auto& tile : sp_set->getValidatedTiles()) {
    insertTile(tile);
  }
}

cs_ptr<Set>
SetWidget::getSet()
{
  return _sp_set;
}

void
SetWidget::insertTile(const Tile& tile)
{
  auto* p_tile = new TileWidget();
  p_tile->setTile(tile);
  connect(p_tile, &TileWidget::chosen,
          this, &SetWidget::onTileChosen);
  ui->tilesLayout->addWidget(p_tile);
}

void
SetWidget::removeTile(const Tile& tile)
{
  const auto& children = findChildren<TileWidget*>();
  for (auto* p_tileWidget : children) {
    if (p_tileWidget->getTile() == tile) {
      if (children.size() == 1) {
        deleteLater();
      } else {
        p_tileWidget->deleteLater();
      }
      break;
    }
  }
}

void
SetWidget::dragEnterEvent(QDragEnterEvent* event)
{
  ui->addLabel->setVisible(true);
  event->accept();
}

void
SetWidget::dragLeaveEvent(QDragLeaveEvent* event)
{
  ui->addLabel->setVisible(false);
  event->accept();
}

void
SetWidget::dropEvent(QDropEvent* event)
{
  ui->addLabel->setVisible(false);
  event->accept();
  emit chosen();
}

void
SetWidget::onTileChosen()
{
  auto* p_tileWidget = qobject_cast<TileWidget*>(sender());
  if (p_tileWidget) {
    qDebug() << "SetWidget emit tile Chosen";
    emit tileChosen(p_tileWidget);
  }
}

} // namespace game
} // namespace rummikub
