#ifndef RUMMIKUB_CORE__PLAYER_H
#define RUMMIKUB_CORE__PLAYER_H

#include "CoreFwd.h"
#include "Holder.h"

#include <memory>
#include <map>

namespace rummikub {
namespace core {

class Player {
protected:
  Player(const Player&) = default;
  Player& operator=(const Player&) = default;
  Player(Player&&) = default;
  Player& operator=(Player&&) = default;

public:
  static std::shared_ptr<Player> newPlayer();

  virtual std::shared_ptr<Player> clone() const;

  Player();
  ~Player();

  void addTile(const Tile& tile, size_t count = 1);
  bool removeTile(const Tile& tile, size_t count = 1);
  void clearTiles();
  bool hasTile(const Tile& tile) const;
  size_t count(const Tile& tile) const;
  std::vector<Tile> getKinds() const;
  bool empty() const;

  std::weak_ptr<Agent> getAgent();
  void setAgent(const std::shared_ptr<Agent>&);

private:
  struct Member;
  Member* _;
};

void copyTiles(const std::shared_ptr<Player>& to,
               const std::shared_ptr<const Player>& from);

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__PLAYER_H

