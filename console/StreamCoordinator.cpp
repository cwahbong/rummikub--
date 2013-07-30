#include "StreamCoordinator.h"

#include "model/Tile.h"

#include <map>

using std::istream;
using std::make_shared;
using std::map;
using std::ostream;
using std::string;

namespace rummikub {

struct StreamCoordinator::Member {
  istream& is;
  ostream& os;
};

StreamCoordinator::StreamCoordinator(istream& is, ostream& os)
  : Agent{}, EventReceiver{}, _{new Member{is, os}}
{
}

StreamCoordinator::~StreamCoordinator()
{/* Empty. */}

// Agent

void
StreamCoordinator::response(const s_ptr<Delegate>& sp_delegate)
{
}

// EventReceiver

void
StreamCoordinator::tilePut(
    const cs_ptr<Hand>&,
    const Tile& tile,
    const cs_ptr<Set>&) {
  _->os << "Player puts tile (" << tile.getColorName() << ", "
        << tile.getValueName() << ")\n";
}

/// TODO

} // namespace rummikub

