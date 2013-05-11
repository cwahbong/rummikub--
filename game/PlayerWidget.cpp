#include "PlayerWidget.h"
#include "ui_PlayerWidget.h"

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

/*
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
*/

} // namespace game
} // namespace rummikub

