#include "Game.h"

#include "model/Rummikub.h"

#include <set>

using std::make_shared;
using std::set;
using std::vector;

namespace rummikub {
namespace core {

struct Game::Member {
  const s_ptr<EventReceiver> eventReceiver;
};

Game::Game(const s_ptr<EventReceiver>& eventReceiver)
  : _{new Member{
      eventReceiver
    }}
{/* Empty. */}

Game::~Game()
{/* Empty. */}

s_ptr<EventReceiver>
Game::getEventReceiver() const
{
  return _->eventReceiver;
}

void
startGame(const s_ptr<EventReceiver>& sp_eventReceiver, const vector<s_ptr<Agent>>& sp_agents)
{
  // Cannot use make_shared because of the constructor of Game is protected.
  const auto& sp_game = s_ptr<Game>(new Game(sp_eventReceiver));
  const auto& sp_rummikub = make_shared<Rummikub>(sp_game, sp_agents);
  sp_rummikub->startGame();
}

} // namespace core
} // namespace rummikub

