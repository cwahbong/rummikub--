#include "qmodel/Rummikub.h"

#include "qmodel/Table.h"

#include "model/Rummikub.h"
#include "model/Table.h"

using std::make_shared;

namespace rummikub {
namespace qmodel {

Rummikub::Rummikub(core::Rummikub* rummikub, QObject *parent)
  : QObject{parent},
    m_rummikub{rummikub},
    m_table{make_shared<Table>(rummikub->getTable().get())},
    m_sp_turnStartCallback{make_shared<core::Rummikub::TurnCallback>(
      [this](const cs_ptr<core::Player>& sp_player) {
        emit turnStarted(m_playerMap[sp_player]);
      }
    )},
    m_sp_turnEndCallback{make_shared<core::Rummikub::TurnCallback>(
      [this](const cs_ptr<core::Player>& sp_player) {
        emit turnEnded(m_playerMap[sp_player]);
      }
    )}
{
  for (const auto& sp_player : rummikub->getPlayers()) {
    m_playerMap[sp_player] = make_shared<Player>(sp_player.get());
  }
  m_rummikub->addTurnStartCallback(m_sp_turnStartCallback);
  m_rummikub->addTurnEndCallback(m_sp_turnEndCallback);
}

Rummikub::~Rummikub()
{
  m_rummikub->delTurnStartCallback(m_sp_turnStartCallback);
  m_rummikub->delTurnEndCallback(m_sp_turnEndCallback);
}

} // namespace qmodel
} // namespace rummikub

