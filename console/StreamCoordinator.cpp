#include "StreamCoordinator.h"

#include "OutputFormatter.h"

#include "model/Hand.h"
#include "model/Set.h"
#include "model/Table.h"
#include "model/Tile.h"
#include "StdMemory.h"

#include <boost/tokenizer.hpp>
  using boost::tokenizer;

#include <istream>
  using std::istream;
#include <map>
  using std::map;
#include <ostream>
  using std::ostream;
#include <stdexcept>
  using std::invalid_argument;
  using std::out_of_range;
#include <string>
  using std::string;

namespace rummikub {

namespace {

enum class _Cmd {
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

_Cmd
_to_cmd(const string& str) {
  try {
    return _CMD_MAP.at(str);
  }
  catch (const out_of_range& oor) {
    throw invalid_argument("wrong cmd string");
  }
}

size_t
_to_idx(const string& str) {
  if (str.size() == 0) {
    throw invalid_argument("Empty string @ _to_idx");
  }
  if (str.size() > 3) {
    throw invalid_argument("String size too long @ _to_idx");
  }
  return std::stoul(str);
}

} // namespace rummikuc::<anonymous>

struct StreamCoordinator::Member {
  istream& is;
  ostream& os;
  OutputFormatter outputFormatter;

  string
  getLine()
  {
    string result;
    getline(is, result);
    return result;
  }

  void
  printWhole(const s_ptr<Delegate>& sp_delegate) const
  {
    os << "Table:\n";
    os << outputFormatter.format(sp_delegate->getTable());
    os << "Player:\n";
    os << outputFormatter.format(sp_delegate->getHand());
  }

  template <typename IteratorToString>
  bool
  argsNotEnough(
      IteratorToString begin,
      IteratorToString end) const
  {
    if (begin == end) {
      os << "Arguments not enough.\n";
      return true;
    }
    return false;
  }

  template <typename IteratorToString>
  bool
  argsTooMuch(
      IteratorToString begin,
      IteratorToString end) const
  {
    if (begin != end) {
      os << "Arguments too much.\n";
      return true;
    }
    return false;
  }

  template <typename IteratorToString>
  void
  executePut(
      IteratorToString begin,
      IteratorToString end,
      const s_ptr<Delegate>& sp_delegate) const
  {
    try {
      if (argsNotEnough(begin, end)) {
        return;
      }
      size_t tileOffset = _to_idx(*begin++);
      size_t setOffset;
      bool useExistingSet = (begin != end);
      if (useExistingSet) {
        setOffset = _to_idx(*begin++);
      }
      if (argsTooMuch(begin, end)) {
        return;
      }

      const auto& tiles = sp_delegate->getHand()->getKinds();
      const auto& tile = tiles.at(tileOffset);
      if (useExistingSet) {
        const auto& sp_set = sp_delegate->getTable()->getSets().at(setOffset).lock();
        sp_delegate->putTile(tile, sp_set);
      }
      else {
        sp_delegate->putTile(tile);
      }
    }
    catch (const out_of_range& oor) {
      os << "The index of tile or set is not correct.\n";
    }
    catch (const invalid_argument& ia) {
      os << "The index of tile or set must be a number.\n";
    }
  }

  template <typename IteratorToString>
  void
  executeMove(
      IteratorToString begin,
      IteratorToString end,
      const s_ptr<Delegate>& sp_delegate) const
  {
    try {
      if (argsNotEnough(begin, end)) {
        return;
      }
      size_t tileOffset = _to_idx(*begin++);
      if (argsNotEnough(begin, end)) {
        return;
      }
      size_t fromOffset = _to_idx(*begin++);
      if (argsNotEnough(begin, end)) {
        return;
      }
      bool useExistSetTo = (begin != end);
      size_t toOffset;
      if (useExistSetTo) {
        toOffset = _to_idx(*begin++);
      }
      if (argsTooMuch(begin, end)) {
        return;
      }

      const auto& sp_fromSet = sp_delegate->getTable()->getSets().at(fromOffset).lock();
      auto tile = sp_fromSet->getValidatedTiles().at(tileOffset);
      if (useExistSetTo) {
        const auto& sp_toSet = sp_delegate->getTable()->getSets().at(toOffset).lock();
        sp_delegate->moveTile(tile, sp_fromSet, sp_toSet);
      }
      else {
        // TODO move to an empty set
        // sp_delegate->moveTile(tile, sp_fromSet);
        os << "BONG! move to an empty set is not implemented.\n";
      }
    }
    catch (const out_of_range& oor) {
      os << "The index of tile or set is not correct.\n";
    }
    catch (const invalid_argument& ia) {
      os << "The index of tile or set must be a number.\n";
    }
  }

  template <typename IteratorToString>
  void
  executeRestore(
      IteratorToString begin,
      IteratorToString end,
      const s_ptr<Delegate>& sp_delegate) const
  {
    if (begin != end) {
      os << "Arguments too much.\n";
      return;
    }
    sp_delegate->restore();
  }
};

StreamCoordinator::StreamCoordinator(istream& is, ostream& os)
  : Agent{}, EventReceiver{},
    _{new Member{is, os, defaultOutputFormatter()}}
{/* Empty. */}

StreamCoordinator::~StreamCoordinator()
{/* Empty. */}

// Agent

void
StreamCoordinator::response(const s_ptr<Delegate>& sp_delegate) const
{
  while (true) {
    _->printWhole(sp_delegate);

    // NOTE: tokenizer does not keep a copy of string, so we cannot
    // destructe the string until the parsing is done.
    const string& line =_->getLine();
    tokenizer<> t(line);
    auto begin = t.begin();
    auto end = t.end();
    if (begin == end) {
      _->os << "Empty line...\n";
      continue;
    }
    try {
      const auto& cmd = _to_cmd(*begin++);
      switch (cmd) {
      case _Cmd::PUT:
        _->executePut(begin, end, sp_delegate);
        break;
      case _Cmd::MOVE:
        _->executeMove(begin, end, sp_delegate);
        break;
      case _Cmd::RESTORE:
        _->executeRestore(begin, end, sp_delegate);
        break;
      case _Cmd::END:
        if (!_->argsTooMuch(begin, end)) {
          return;
        }
      }
    }
    catch (const invalid_argument& ia) {
      _->os << "Wrong command type.\n";
    }
  }
}

// EventReceiver

void
StreamCoordinator::tilePut(
    const cs_ptr<Player>&,
    const Tile& tile,
    const cs_ptr<Set>&) {
  _->os << "Player puts tile (" << tile.getColor() << ", "
        << tile.getValue() << ")\n";
}

/// TODO

} // namespace rummikub

