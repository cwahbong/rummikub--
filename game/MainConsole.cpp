#include "MainConsole.h"

#include "CoreFwd.h"
#include "Agent.h"
#include "Player.h"
#include "Rummikub.h"
#include "Set.h"
#include "Tile.h"

#include <array>
#include <iostream>
#include <map>
#include <memory>
#include <string>

#include <QCoreApplication>

using std::array;
using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::map;
using std::shared_ptr;
using std::string;

using rummikub::core::Agent;
using rummikub::core::AgentDelegate;
using rummikub::core::Player;
using rummikub::core::Rummikub;
using rummikub::core::Table;

namespace rummikub {
namespace game {

class ConsoleAgent : public Agent {
private:
  enum CmdType {PUT, MOVE, RESTORE, END};
  static const map<string, CmdType> CMD_MAP;

public:
  void response(const shared_ptr<const AgentDelegate>& sp_delegate)
  {
    while (true) {
      cout << "Table:\n";
      for (auto& wp_set : sp_delegate->getTable().getSets()) {
        const auto& sp_set = wp_set.lock();
        for (const auto& tile : sp_set->getValidatedTiles()) {
          cout << "(" << tile.getValue() << ") ";
        }
        cout << "\n";
      }
      cout << "Player:\n";
      for (const auto& pair : sp_delegate->getPlayer().getTiles()) {
        for (int i=0; i<pair.second; ++i) {
          cout << "(" << pair.first.getValue() << ") ";
        }
      }
      cout << endl;
      string input;
      getline(cin, input);
      switch (CMD_MAP.at(input)) {
      case PUT:
        // TODO parse tile and set
        // sp_delegate->putTile(tile, set);
        break;
      case MOVE:
        // TODO parse tile and sets
        // sp_delegate->moveTile(tile, from, to);
        break;
      case RESTORE:
        sp_delegate->restore();
        break;
      case END:
        return;
      }
    }
  }
};

const map<string, ConsoleAgent::CmdType> ConsoleAgent::CMD_MAP = {
  {"put", ConsoleAgent::PUT},
  {"move", ConsoleAgent::MOVE},
  {"restore", ConsoleAgent::RESTORE},
  {"end", ConsoleAgent::END},
};

void
MainConsole::start()
{
  array<shared_ptr<Agent>, 2> sp_agents;
  sp_agents.fill(shared_ptr<Agent>{new ConsoleAgent{}});
  Rummikub rummikub{sp_agents.begin(), sp_agents.end()};
  rummikub.addTurnStartCallback([](const shared_ptr<const Player>&){
    cout << "turn start\n";
  });
  rummikub.addTurnEndCallback([](const shared_ptr<const Player>&){
    cout << "turn end\n";
  });
  rummikub.addGameEndCallback([](){cout << "game end.\n";});
  rummikub.startGame();
  emit end();
}

} // namespace game
} // namespace rummikub

