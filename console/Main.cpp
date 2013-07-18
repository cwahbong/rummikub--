#include "ConsoleAgent.h"
#include "ConsoleReceiver.h"

#include "Agent.h"
#include "Rummikub.h"
#include "StdMemory.h"

#include <array>
#include <iostream>
#include <vector>

using rummikub::Agent;
using rummikub::ConsoleAgent;
using rummikub::ConsoleReceiver;
using rummikub::Rummikub;
using rummikub::s_ptr;

using std::array;
using std::make_shared;
using std::vector;

int
main(int argc, char* argv[])
{
  // TODO parse argument and make console ui more user friendly.
  array<s_ptr<Agent>, 1> sp_agents;
  sp_agents.fill(make_shared<ConsoleAgent>());
  Rummikub(make_shared<ConsoleReceiver>(),
      vector<s_ptr<Agent>>(begin(sp_agents), end(sp_agents))).startGame();
  return 0;
}

