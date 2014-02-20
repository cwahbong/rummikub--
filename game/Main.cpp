#include "Player.h"
  using rummikub::Player;
#include "StdMemory.h"
  using rummikub::cs_ptr;

#include "MainWindow.h"
  using rummikub::game::MainWindow;

#include <QApplication>
#include <QMetaType>

void
registerMetaTypes()
{
  qRegisterMetaType<cs_ptr<Player>>("cs_ptr<Player>");
}

int
main(int argc, char* argv[])
{
  registerMetaTypes();
  QApplication app(argc, argv);
  MainWindow mainWindow;
  mainWindow.show();
  return app.exec();
}
