#ifndef RUMMIKUB_QCORE__PLAYER_H
#define RUMMIKUB_QCORE__PLAYER_H

#include "Fwd.h"

#include "CoreFwd.h"
#include "StdMemory.h"

#include <QObject>

namespace rummikub {
namespace qmodel {

class Player : public QObject {
  Q_OBJECT

public:
  explicit Player(const s_ptr<core::Player>&, QObject *parent = 0);
  ~Player();

signals:
  void tileInserted(const Tile&);
  void tileRemoved(const Tile&);

private:
  struct Member;
  u_ptr<Member> _;
};

} // namespace qmodel
} // namespace rummikub

#endif // RUMMIKUB_QCORE__PLAYER_H

