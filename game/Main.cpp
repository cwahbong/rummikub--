#include "StdMemory.h"
  using rummikub::make_s;

#include "MainWindow.h"
  using rummikub::game::MainWindow;

#include <QApplication>

using std::make_shared;

int
main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  auto sp_window = make_s<MainWindow>();
  sp_window->show();
  return app.exec();
}

