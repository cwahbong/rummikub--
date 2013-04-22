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
  const s_ptr<core::Rummikub> m_rummikub;
  cs_ptr<Table> m_table;
  s_ptr<core::Rummikub::TurnCallback> m_sp_turnStartCallback;
  s_ptr<core::Rummikub::TurnCallback> m_sp_turnEndCallback;
  std::map<cs_ptr<core::Player>, cs_ptr<Player>> m_playerMap;
};

} // namespace qmodel
} // namespace rummikub

#endif // RUMMIKUB_QCORE__RUMMIKUB_H

