#include "SetWidget.h"
#include "ui_SetWidget.h"

#include "TileWidget.h"

#include "model/Tile.h"

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

/*
void
SetWidget::insertTile(const Tile& tile)
{
  auto* p_tile = new TileWidget();
  p_tile->setTile(tile);
  layout()->addWidget(p_tile);
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
*/

} // namespace game
} // namespace rummikub
