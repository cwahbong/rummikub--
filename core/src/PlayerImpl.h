/**
 * INTERNAL HEADER, DO NOT INCLUDE EXTERNALLY!!!
 */
#include "Player.h"

#include "Tile.h"

using std::shared_ptr;
using std::map;
using std::weak_ptr;

namespace rummikub {
namespace core {

class PlayerImpl : public Player {
private:
  shared_ptr<Agent> m_sp_agent{};
  map<Tile, int> m_tilemap{};

protected:
  PlayerImpl(const PlayerImpl&) = default;
  PlayerImpl& operator=(const PlayerImpl&) = default;

public:
  PlayerImpl() = default;

  shared_ptr<Player> clone();

  void addTile(Tile tile);
  bool removeTile(Tile tile);
  bool empty();
  const map<Tile, int>& getTiles() const;

  weak_ptr<Agent> getAgent();
  void setAgent(const shared_ptr<Agent>&);
};

} // namespace core
} // namespace rummikub

