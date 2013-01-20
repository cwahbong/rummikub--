#include <QApplication>

#include "MainWindow.h"

#include <cstring>
#include <memory>

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
  if (useGui) {
    sp_window = make_shared<MainWindow>();
    sp_window->show();
  } else {
    // TODO console ver
  }
  return app.exec();
}

