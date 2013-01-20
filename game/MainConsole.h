#ifndef RUMMIKUB_GAME__MAINCONSOLE_H
#define RUMMIKUB_GAME__MAINCONSOLE_H

#include <QObject>

namespace rummikub {
namespace game {

class MainConsole : public QObject {
  Q_OBJECT

public slots:
  void start();

signals:
  void end();
};

} // game
} // rummikub

#endif // RUMMIKUB_GAME__MAINCONSOLE_H

