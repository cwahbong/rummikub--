#ifndef RUMMIKUB_QCORE__PLAYER_H
#define RUMMIKUB_QCORE__PLAYER_H

#include "CoreFwd.h"
#include "StdMemory.h"

#include <QObject>

namespace rummikub {
namespace qmodel {

class Player : public QObject {
  Q_OBJECT
  using Tile = core::Tile;

public:
  explicit Player(core::Player* player, QObject *parent = 0);
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

