#include "MainConsole.h"
#include "MainWindow.h"

#include <cstring>
#include <memory>

#include <QApplication>
#include <QObject>
#include <QTimer>

using rummikub::game::MainConsole;
using rummikub::game::MainWindow;

using std::make_shared;
using std::shared_ptr;
using std::strcmp;

int main(int argc, char* argv[])
{
#ifdef Q_WS_X11
  bool useGui = getenv("DISPLAY") != 0;
#else // Q_WS_X11
  bool useGui = true;
#endif // Q_WS_X11
  for (int i=0; i<argc; ++i) {
    if (strcmp(argv[i], "--nogui")==0) {
      useGui = false;
    }
  }
  QApplication app(argc, argv, useGui);
  shared_ptr<MainWindow> sp_window;
  shared_ptr<MainConsole> sp_console;
  if (useGui) {
    sp_window = make_shared<MainWindow>();
    sp_window->show();
  } else {
    sp_console = make_shared<MainConsole>();
    QObject::connect(sp_console.get(), SIGNAL(end()), &app, SLOT(quit()));
    QTimer::singleShot(0, sp_console.get(), SLOT(start()));
  }
  return app.exec();
}

