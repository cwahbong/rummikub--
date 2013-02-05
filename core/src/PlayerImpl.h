/**
 * INTERNAL HEADER, DO NOT INCLUDE EXTERNALLY!!!
 */
#include "Player.h"

#include "Holder.h"
#include "Tile.h"

using std::shared_ptr;
using std::vector;
using std::weak_ptr;

namespace rummikub {
namespace core {

class PlayerImpl : public Player {
private:
  shared_ptr<Agent> m_sp_agent{};
  Holder<Tile> m_holder{};

protected:
  PlayerImpl(const PlayerImpl&) = default;
  PlayerImpl& operator=(const PlayerImpl&) = default;

public:
  PlayerImpl() = default;

  shared_ptr<Player> clone() const;

  void addTile(const Tile& tile, size_t count = 1);
  bool removeTile(const Tile& tile, size_t count = 1);
  void clearTiles();
  bool hasTile(const Tile& tile) const;
  size_t count(const Tile& tile) const;
  bool empty() const;
  vector<Tile> getKinds() const;

  weak_ptr<Agent> getAgent();
  void setAgent(const shared_ptr<Agent>&);
};

} // namespace core
} // namespace rummikub

