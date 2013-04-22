#ifndef RUMMIKUB_QCORE__PLAYER_H
#define RUMMIKUB_QCORE__PLAYER_H

#include "CoreFwd.h"
#include "Player.h"
#include "StdMemory.h"

#include <QObject>

namespace rummikub {
namespace qmodel {

class Player : public QObject {
  Q_OBJECT

public:
  explicit Player(core::Player* player, QObject *parent = 0);

signals:

private:
  const s_ptr<core::Player> m_player;
};

} // namespace qmodel
} // namespace rummikub

#endif // RUMMIKUB_QCORE__PLAYER_H

