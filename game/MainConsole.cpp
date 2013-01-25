#include "MainConsole.h"

#include "CoreFwd.h"
#include "Agent.h"
#include "Player.h"
#include "Rummikub.h"

#include <array>
#include <iostream>
#include <memory>

#include <QCoreApplication>

using std::array;
using std::cout;
using std::cin;
using std::endl;
using std::shared_ptr;

using rummikub::core::Player;
using rummikub::core::Rummikub;

namespace rummikub {
namespace game {

/* class ConsoleAgent : public Agent {
}; */

void
MainConsole::start()
{
  array<shared_ptr<Player>, 4> sp_players{};
  for (auto& sp_player : sp_players) {
    sp_player = Player::newPlayer();
  }
  Rummikub rummikub{sp_players.begin(), sp_players.end()};
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

}
}

