#include "MainConsole.h"

#include "ConsoleAgent.h"

#include "CoreFwd.h"
#include "EventReceiver.h"
#include "Rummikub.h"
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
  Rummikub(make_shared<ConsoleReceiver>(),
      vector<shared_ptr<Agent>>(sp_agents.begin(), sp_agents.end())).startGame();
  emit end();
}

} // namespace game
} // namespace rummikub

