#ifndef RUMMIKUB_QCORE__CRUMMIKUB_H
#define RUMMIKUB_QCORE__CRUMMIKUB_H

#include "CoreFwd.h"
#include "StdMemory.h"
#include "model/Rummikub.h"

#include "Player.h"
#include "Table.h"

#include <QObject>

#include <map>

namespace rummikub {
namespace qmodel {

class Rummikub : public QObject {
  Q_OBJECT

public:
  explicit Rummikub(core::Rummikub* rummikub, QObject *parent = 0);
  ~Rummikub();
    
signals:
  void gameStarted();
  void gameEnded();

  void turnStarted(const cs_ptr<Player>&);
  void turnEnded(const cs_ptr<Player>&);

private:
  struct Member;
  const u_ptr<Member> _;
};

} // namespace qmodel
} // namespace rummikub

#endif // RUMMIKUB_QCORE__RUMMIKUB_H

