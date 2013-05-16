#include "MainConsole.h"

#include "ConsoleAgent.h"

#include "CoreFwd.h"
#include "AgentDelegate.h"
#include "EventReceiver.h"
#include "Game.h"
#include "model/Hand.h"
#include "model/Tile.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <vector>

using std::array;
using std::cout;
using std::make_shared;
using std::shared_ptr;
using std::vector;

using rummikub::core::startGame;
using rummikub::core::Agent;
using rummikub::core::EventReceiver;
using rummikub::core::Hand;
using rummikub::core::Set;
using rummikub::core::Tile;

namespace rummikub {
namespace game {

class ConsoleReceiver : public EventReceiver {
public:
  virtual void tilePut(const cs_ptr<Hand>& sp_player,
                       const Tile& tile,
                       const cs_ptr<Set>& sp_set) override {
    cout << "Player puts tile (" << tile.getColorName() << ", "
         << tile.getValueName() << ")\n";
  }
  // TODO implement other functions.
};

void
MainConsole::start()
{
  array<shared_ptr<Agent>, 1> sp_agents;
  sp_agents.fill(make_shared<ConsoleAgent>());
  if (!sp_agents[0]) {
    std::cerr << "EEEEE\n";
  } else {
    std::cerr << "OOOOO\n";
  }
  startGame(make_shared<ConsoleReceiver>(),
            vector<shared_ptr<Agent>>(sp_agents.begin(), sp_agents.end()));
  emit end();
}

} // namespace game
} // namespace rummikub

