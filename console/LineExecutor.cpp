#include "LineExecutor.h"

#include "model/Hand.h"
#include "model/Set.h"
#include "model/Table.h"
#include "model/Tile.h"
#include "Agent.h"

#include <istream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

using std::istream;
using std::istringstream;
using std::map;
using std::out_of_range;
using std::string;

#include <iostream>

namespace rummikub {

namespace {

enum class _Cmd {
    INVALID,
    PUT,
    MOVE,
    RESTORE,
    END,
};

const map<string, _Cmd> _CMD_MAP = {
    {"put", _Cmd::PUT},
    {"move", _Cmd::MOVE},
    {"restore", _Cmd::RESTORE},
    {"end", _Cmd::END},
};

istream&
operator>>(istream& is, _Cmd& cmd)
{
  string cmdStr;
  is >> cmdStr;
  cmd = _CMD_MAP.at(cmdStr);
  return is;
}

void
_extractPutResponse(
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
_extractMoveResponse(
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

bool
_executeLine(const string& line, const s_ptr<Agent::Delegate>& sp_delegate)
{
  istringstream iss(line);
  _Cmd cmd;
  try {
    iss >> cmd;
  } catch (const out_of_range&) {
    // os << "Bad command.\n";
  }
  switch (cmd) {
  case _Cmd::PUT:
    _extractPutResponse(iss, sp_delegate);
    break;
  case _Cmd::MOVE:
    _extractMoveResponse(iss, sp_delegate);
    break;
  case _Cmd::RESTORE:
    sp_delegate->restore();
    break;
  case _Cmd::END:
    return false;
  }
  return true;
}

} // namespace

LineExecutor
defaultLineExecutor()
{
  return _executeLine;
}

} // namespace rummikub
