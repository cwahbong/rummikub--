/**
 * INTERNAL HEADER, DO NOT INCLUDE EXTERNALLY!!!
 */
#include "Player.h"

#include "Tile.h"

#include <vector>

using std::shared_ptr;
using std::vector;
using std::weak_ptr;

namespace rummikub {
namespace core {

class PlayerImpl : public Player {
private:
  shared_ptr<Agent> m_sp_agent{};
  vector<Tile> m_tiles{};

public:
  void addTile(Tile tile);
  bool removeTile(Tile tile);
  bool empty();
  weak_ptr<Agent> getAgent();
  void setAgent(const shared_ptr<Agent>&);
};

} // namespace core
} // namespace rummikub

