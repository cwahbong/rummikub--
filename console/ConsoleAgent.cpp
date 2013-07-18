#include "ConsoleAgent.h"

#include "model/Hand.h"
#include "model/Set.h"
#include "model/Table.h"
#include "model/Tile.h"
#include "StdMemory.h"

#include <exception>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::exception;
using std::istringstream;
using std::map;
using std::string;
using std::vector;

namespace rummikub {

namespace {

enum CmdType {
    PUT,
    MOVE,
    RESTORE,
    END,
};

const map<string, CmdType> CMD_MAP = {
    {"put", PUT},
    {"move", MOVE},
    {"restore", RESTORE},
    {"end", END},
};

void
printTile(const Tile& tile) {
  cout << "(" << tile.getColorName()
       << " " << tile.getValueName() << ")";
}

void
printTable(const cs_ptr<Agent::Delegate>& sp_delegate)
{
  for (const auto& wp_set : sp_delegate->getTable()->getSets()) {
    const auto& sp_set = wp_set.lock();
    for (const auto& tile : sp_set->getValidatedTiles()) {
      printTile(tile);
    }
    cout << endl;
  }
}

void
printTiles(
    const cs_ptr<Agent::Delegate>& sp_delegate,
    const vector<Tile>& tiles)
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

void
printWhole(const cs_ptr<Agent::Delegate>& sp_delegate)
{
  cout << "Table:\n";
  printTable(sp_delegate);
  cout << "Player:\n";
  printTiles(sp_delegate, sp_delegate->getHand()->getKinds());
}

CmdType
extractCommand(istringstream& iss)
{
  string cmd;
  iss >> cmd;
  return CMD_MAP.at(cmd);
}

void
extractPutResponse(
    istringstream& iss,
    const s_ptr<Agent::Delegate>& sp_delegate)
{
  int tileOffset, setOffset;
  iss >> tileOffset;
  const auto& tiles = sp_delegate->getHand()->getKinds();
  const auto& tile = tiles[tileOffset];
  if (iss >> setOffset) {
    const auto& sp_set = sp_delegate->getTable()->getSets()[setOffset].lock();
    sp_delegate->putTile(tile, sp_set);
  } else {
    sp_delegate->putTile(tile);
  }
}

void
extractMoveResponse(
    istringstream& iss,
    const s_ptr<Agent::Delegate>& sp_delegate)
{
  int tileOffset;
  iss >> tileOffset;
  int fromOffset, toOffset;
  iss >> fromOffset >> toOffset;
  const auto& sp_fromSet = sp_delegate->getTable()->getSets()[fromOffset].lock();
  auto tile = sp_fromSet->getValidatedTiles()[tileOffset];
  const auto& sp_toSet = sp_delegate->getTable()->getSets()[toOffset].lock();
  sp_delegate->moveTile(tile, sp_fromSet, sp_toSet);
}

} // namespace

void
ConsoleAgent::response(const s_ptr<Agent::Delegate>& sp_delegate)
{
  while (true) {
    printWhole(sp_delegate);
    string input;
    getline(cin, input);
    istringstream iss(input);
    try {
      switch (extractCommand(iss)) {
      case PUT:
        extractPutResponse(iss, sp_delegate);
        break;
      case MOVE:
        extractMoveResponse(iss, sp_delegate);
        break;
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

} // namsepace rummikub

