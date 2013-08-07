#include "StreamCoordinator.h"

#include "LineExecutor.h"
#include "OutputFormatter.h"

#include "model/Tile.h"
#include "StdMemory.h"

#include <istream>
  using std::istream;
#include <map>
  using std::map;
#include <ostream>
  using std::ostream;
#include <string>
  using std::string;

namespace rummikub {

struct StreamCoordinator::Member {
  istream& is;
  ostream& os;
  LineExecutor lineExecutor;
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
};

StreamCoordinator::StreamCoordinator(istream& is, ostream& os)
  : Agent{}, EventReceiver{},
    _{new Member{is, os, defaultLineExecutor(), defaultOutputFormatter()}}
{/* Empty. */}

StreamCoordinator::~StreamCoordinator()
{/* Empty. */}

// Agent

void
StreamCoordinator::response(const s_ptr<Delegate>& sp_delegate) const
{
  while (true) {
    _->printWhole(sp_delegate);
    const auto& line = _->getLine();
    if (!_->lineExecutor(line, sp_delegate)) break;
  }
}

// EventReceiver

void
StreamCoordinator::tilePut(
    const cs_ptr<Player>&,
    const Tile& tile,
    const cs_ptr<Set>&) {
  _->os << "Player puts tile (" << tile.getColorName() << ", "
        << tile.getValueName() << ")\n";
}

/// TODO

} // namespace rummikub

