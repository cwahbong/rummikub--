#include "GameWidget.h"
#include "ui_GameWidget.h"

namespace rummikub {
namespace game {

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget)
{
    ui->setupUi(this);
}

GameWidget::~GameWidget()
{
    delete ui;
}

} // namespace game
} // namespace rummikub

