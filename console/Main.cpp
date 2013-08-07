#include "StreamCoordinator.h"
  using rummikub::StreamCoordinator;


#include "Agent.h"
  using rummikub::Agent;
#include "Rummikub.h"
  using rummikub::Rummikub;
#include "StdMemory.h"
  using rummikub::make_s;
  using rummikub::s_ptr;


#include <array>
  using std::array;
#include <iostream>
  using std::cin;
  using std::cout;
#include <vector>
  using std::vector;


int
main(int argc, char* argv[])
{
  // TODO parse argument and make console ui more user friendly.
  const auto& coordinator = make_s<StreamCoordinator>(cin, cout);
  Rummikub(coordinator, {
    {"Player 1", coordinator},
    {"Player 2", coordinator},
  }).startGame();
  return 0;
}

