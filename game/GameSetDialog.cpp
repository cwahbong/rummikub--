#include "GameSetDialog.h"
#include "ui_GameSetDialog.h"

namespace rummikub {
namespace game {

GameSetDialog::GameSetDialog(QWidget *parent)
  : QDialog(parent),
    ui(new Ui::GameSetDialog)
{
  ui->setupUi(this);
}

GameSetDialog::~GameSetDialog()
{
  delete ui;
}

int
GameSetDialog::getPlayerNum()
{
  return ui->m_playerNumberSpinBox->value();
}

} // namespace game
} // namespace rummikub
