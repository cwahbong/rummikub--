#include "EventReceiver.h"

namespace rummikub {

class ConsoleReceiver : public EventReceiver {
public:
  void tilePut(const cs_ptr<Hand>& sp_player,
               const Tile& tile,
               const cs_ptr<Set>& sp_set) override;
  // TODO implement other functions.
};

} // namespace rummikub

