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
  const auto coordinator = make_shared<StreamCoordinator>(cin, cout);
  array<s_ptr<Agent>, 1> sp_agents;
  sp_agents.fill(coordinator);
  Rummikub(coordinator,
     vector<s_ptr<Agent>>(begin(sp_agents), end(sp_agents))).startGame();
  return 0;
}

