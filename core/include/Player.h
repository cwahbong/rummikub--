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
  Player() = default;

  Player(const Player&) = default;
  Player& operator=(const Player&) = default;
  Player(Player&&) = default;
  Player& operator=(Player&&) = default;

public:
  static std::shared_ptr<Player> newPlayer();

  virtual std::shared_ptr<Player> clone() const = 0;

  virtual void addTile(const Tile& tile) = 0;
  virtual bool removeTile(const Tile& tile) = 0;
  virtual bool hasTile(const Tile& tile) const = 0;
  virtual size_t count(const Tile& tile) const = 0;
  virtual std::vector<Tile> getKinds() const = 0;
  virtual bool empty() const = 0;

  virtual std::weak_ptr<Agent> getAgent() = 0;
  virtual void setAgent(const std::shared_ptr<Agent>&) = 0;
};

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__PLAYER_H

