#include "ConsoleReceiver.h"

#include "model/Tile.h"

#include <iostream>

using std::cout;

namespace rummikub {

void
ConsoleReceiver::tilePut(const cs_ptr<Hand>& sp_player,
                         const Tile& tile,
                         const cs_ptr<Set>& sp_set)
{
  cout << "Player puts tile (" << tile.getColorName() << ", "
       << tile.getValueName() << ")\n";
}

} // namespace rummikub

