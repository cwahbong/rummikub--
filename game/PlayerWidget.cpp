#include "PlayerWidget.h"
#include "ui_PlayerWidget.h"

#include "TileWidget.h"

namespace rummikub {
namespace game {

PlayerWidget::PlayerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerWidget)
{
    ui->setupUi(this);
}

PlayerWidget::~PlayerWidget()
{
    delete ui;
}

void
PlayerWidget::setTiles(const cs_ptr<Hand>& sp_hand)
{
  for (auto* p_tileWidget : findChildren<TileWidget*>()) {
    delete p_tileWidget;
  }
  auto* p_layout = ui->tilesLayout;
  for (const auto& tile : sp_hand->getKinds()) {
    for (auto c = sp_hand->count(tile); c > 0; --c) {
      auto* p_tileWidget = new TileWidget();
      p_tileWidget->setTile(tile);
      connect(p_tileWidget, &TileWidget::chosen,
              this, &PlayerWidget::onTileChosen);
      connect(p_tileWidget, &TileWidget::unchosen,
              this, &PlayerWidget::onTileUnchosen);
      p_layout->addWidget(p_tileWidget);
    }
  }
}

void
PlayerWidget::insertTile(const Tile&)
{
  // TODO
}

void
PlayerWidget::removeTile(const Tile&)
{
  // TODO
}

void
PlayerWidget::onTileChosen()
{
  auto* p_tileWidget = qobject_cast<TileWidget*>(sender());
  emit tileChosen(p_tileWidget, nullptr);
}

void
PlayerWidget::onTileUnchosen()
{
  emit tileChosen(nullptr, nullptr);
}

} // namespace game
} // namespace rummikub

