#include "SetWidget.h"
#include "ui_SetWidget.h"

#include "TileWidget.h"

#include "model/Tile.h"
#include "model/Set.h"

#include <QLayout>

using std::make_shared;

namespace rummikub {
namespace game {

SetWidget::SetWidget(QWidget *parent)
  : QWidget(parent),
    ui(new Ui::SetWidget)
{
  ui->setupUi(this);
}

SetWidget::~SetWidget()
{
  delete ui;
}

void
SetWidget::setSet(const cs_ptr<Set>& sp_set)
{
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
  ui->tilesLayout->addWidget(p_tile);
  // connect(p_tileWidget, &TileWidget::toggled,
  //         this, &PlayerWidget::tileToggled);
}

void
SetWidget::removeTile(const Tile& tile)
{
  for (auto* p_tileWidget : findChildren<TileWidget*>()) {
    if (p_tileWidget->getTile() == tile) {
      p_tileWidget->deleteLater();
      break;
    }
  }
}

} // namespace game
} // namespace rummikub
