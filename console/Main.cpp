#include "StreamCoordinator.h"

#include "Agent.h"
#include "Rummikub.h"
#include "StdMemory.h"

#include <array>
#include <iostream>
#include <vector>

using rummikub::Agent;
using rummikub::Rummikub;
using rummikub::StreamCoordinator;
using rummikub::s_ptr;

using std::array;
using std::cin;
using std::cout;
using std::make_shared;
using std::vector;

int
main(int argc, char* argv[])
{
  // TODO parse argument and make console ui more user friendly.
  const auto& coordinator = make_shared<StreamCoordinator>(cin, cout);
  Rummikub(coordinator, {
    {"Player 1", coordinator},
    {"Player 2", coordinator},
  }).startGame();
  return 0;
}

