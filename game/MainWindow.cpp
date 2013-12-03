#include "MainWindow.h"
#include "ui_MainWindow.h"


#include <iostream>

namespace rummikub {
namespace game {

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  gameSetDialog(new GameSetDialog(this))
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void
MainWindow::on_actionStartNew_triggered(bool)
{
  if (gameSetDialog->exec() == QDialog::Accepted) {
    // TODO starts with specific number of players.
    ui->m_gameWidget->startNewGame();
  }
}

} // namespace game
} // namespace rummikub

