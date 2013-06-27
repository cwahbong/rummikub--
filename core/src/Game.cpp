#include "Game.h"

#include "Rummikub.h"

#include <set>

using std::make_shared;
using std::vector;

namespace rummikub {
namespace core {

struct Game::Member {
  s_ptr<EventReceiver> sp_eventReceiver;
  vector<s_ptr<Agent>> sp_agents;
};

Game::Game(
    const s_ptr<EventReceiver>& sp_eventReceiver,
    const vector<s_ptr<Agent>>& sp_agents) :
  _{new Member{
    sp_eventReceiver,
    sp_agents
  }}
{/* Empty. */}

Game::~Game()
{/* Empty. */}

void
Game::start()
{
  const auto& sp_rummikub = make_shared<Rummikub>(_->sp_eventReceiver, _->sp_agents);
  sp_rummikub->startGame();
}

} // namespace core
} // namespace rummikub

