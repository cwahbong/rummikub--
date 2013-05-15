#include "MainConsole.h"

#include "CoreFwd.h"
#include "Agent.h"
#include "AgentDelegate.h"
#include "EventReceiver.h"
#include "Game.h"
#include "model/Hand.h"
#include "model/Rummikub.h"
#include "model/Set.h"
#include "model/Table.h"
#include "model/Tile.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>

using std::array;
using std::cout;
using std::cin;
using std::endl;
using std::exception;
using std::getline;
using std::istringstream;
using std::make_shared;
using std::map;
using std::ostream;
using std::shared_ptr;
using std::string;
using std::vector;

using rummikub::core::startGame;
using rummikub::core::Agent;
using rummikub::core::AgentDelegate;
using rummikub::core::EventReceiver;
using rummikub::core::Game;
using rummikub::core::Hand;
using rummikub::core::Rummikub;
using rummikub::core::Set;
using rummikub::core::Table;
using rummikub::core::Tile;

namespace rummikub {
namespace game {

class ConsoleAgent : public Agent {
private:
  enum CmdType {PUT, MOVE, RESTORE, END};
  static const map<string, CmdType> CMD_MAP;

  void
  printTile(const Tile& tile) const {
    cout << "(" << tile.getColorName()
         << " " << tile.getValueName() << ")";
  }

  void
  printTable(const shared_ptr<const AgentDelegate>& sp_delegate) const
  {
    cout << "Table:\n";
    for (auto& wp_set : sp_delegate->getTable()->getSets()) {
      const auto& sp_set = wp_set.lock();
      for (const auto& tile : sp_set->getValidatedTiles()) {
        printTile(tile);
      }
      cout << endl;
    }
  }

  void
  printTiles(const shared_ptr<const AgentDelegate>& sp_delegate,
      const std::vector<Tile>& tiles) const
  {
    for (const auto& tile : tiles) {
      printTile(tile);
      auto count = sp_delegate->getHand()->count(tile);
      if (count > 1) {
        cout << "x" << count;
      }
      cout << " ";
    }
    cout << endl;
  }

public:
  void response(const shared_ptr<AgentDelegate>& sp_delegate)
  {
    while (true) {
      printTable(sp_delegate);
      auto tiles = sp_delegate->getHand()->getKinds();
      cout << "Player:\n";
      printTiles(sp_delegate, tiles);
      string input;
      getline(cin, input);
      istringstream iss(input);
      string cmd;
      iss >> cmd;
      try {
        switch (CMD_MAP.at(cmd)) {
        case PUT: {
          int tileOffset, setOffset;
          iss >> tileOffset;
          const auto& tile = tiles[tileOffset];
          if (iss >> setOffset) {
            const auto& sp_set = sp_delegate->getTable()->getSets()[setOffset].lock();
            sp_delegate->putTile(tile, sp_set);
          } else {
            sp_delegate->putTile(tile);
          }
          break;
        }
        case MOVE: {
          int tileOffset;
          iss >> tileOffset;
          int fromOffset, toOffset;
          iss >> fromOffset >> toOffset;
          const auto& sp_fromSet = sp_delegate->getTable()->getSets()[fromOffset].lock();
          auto tile = sp_fromSet->getValidatedTiles()[tileOffset];
          const auto& sp_toSet = sp_delegate->getTable()->getSets()[toOffset].lock();
          sp_delegate->moveTile(tile, sp_fromSet, sp_toSet);
          break;
        }
        case RESTORE:
          sp_delegate->restore();
          break;
        case END:
          return;
        }
      } catch (exception& oor) {
        cout << "Bad command." << endl;
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

