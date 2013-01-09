#include "MainWindow.h"
#include "ui_MainWindow.h"

namespace rummikub {
namespace game {

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

} // namespace game
} // namespace rummikub
