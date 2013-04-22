#include "qmodel/Player.h"

#include "model/Player.h"
#include "model/Set.h"

using std::make_shared;

namespace rummikub {
namespace qmodel {

Player::Player(core::Player* player, QObject *parent)
 : QObject{parent},
   m_player{player}
{
}

} // namespace qmodel
} // namespace rummikub

