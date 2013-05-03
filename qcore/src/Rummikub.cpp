#include "qmodel/Rummikub.h"

#include "qmodel/Table.h"

#include "model/Rummikub.h"
#include "model/Table.h"

using std::make_shared;

namespace rummikub {
namespace qmodel {

struct Rummikub::Member {
  const s_ptr<core::Rummikub> sp_rummikub;
  const cs_ptr<Table> sp_table;
  const s_ptr<core::Rummikub::TurnCallback> sp_turnStartCallback;
  const s_ptr<core::Rummikub::TurnCallback> sp_turnEndCallback;
  std::map<cs_ptr<core::Player>, cs_ptr<Player>> playerMap;
};

Rummikub::Rummikub(const s_ptr<core::Rummikub>& sp_rummikub, QObject *parent)
  : QObject{parent},
    _{new Member{
      sp_rummikub,
      make_shared<Table>(sp_rummikub->getTable()),
      make_shared<core::Rummikub::TurnCallback>(
        [this](const cs_ptr<core::Player>& sp_player) {
          emit turnStarted(_->playerMap[sp_player]);
        }
      ),
      make_shared<core::Rummikub::TurnCallback>(
        [this](const cs_ptr<core::Player>& sp_player) {
          emit turnEnded(_->playerMap[sp_player]);
        }
      )
    }}
{
  for (const auto& sp_player : sp_rummikub->getPlayers()) {
    _->playerMap[sp_player] = make_shared<Player>(sp_player);
  }
  _->sp_rummikub->addTurnStartCallback(_->sp_turnStartCallback);
  _->sp_rummikub->addTurnEndCallback(_->sp_turnEndCallback);
}

Rummikub::~Rummikub()
{
  _->sp_rummikub->delTurnStartCallback(_->sp_turnStartCallback);
  _->sp_rummikub->delTurnEndCallback(_->sp_turnEndCallback);
}

} // namespace qmodel
} // namespace rummikub

