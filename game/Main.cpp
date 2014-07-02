#include "Player.h"
  using rummikub::Player;
#include "StdMemory.h"
  using rummikub::cs_ptr;
#include "model/Set.h"
#include "model/Table.h"
#include "model/Tile.h"
  using rummikub::Set;
  using rummikub::Table;
  using rummikub::Tile;

#include "MainWindow.h"
  using rummikub::game::MainWindow;

#include <QApplication>
#include <QMetaType>

void
registerMetaTypes()
{
  qRegisterMetaType<Tile>("Tile");
  qRegisterMetaType<cs_ptr<Player>>("cs_ptr<Player>");
  qRegisterMetaType<cs_ptr<Set>>("cs_ptr<Set>");
  qRegisterMetaType<cs_ptr<Table>>("cs_ptr<Table>");
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
