#ifndef RUMMIKUB_CORE__PLAYER_H
#define RUMMIKUB_CORE__PLAYER_H

#include "CoreFwd.h"

#include <memory>
#include <map>

namespace rummikub {
namespace core {

class Player {
private:
  Player(const Player&) = delete;
  Player& operator=(const Player&) = delete;

protected:
  Player() = default;

  Player(Player&&) = default;
  Player& operator=(Player&&) = default;

public:
  static std::shared_ptr<Player> newPlayer();

  virtual void addTile(Tile tile) = 0;
  virtual bool removeTile(Tile tile) = 0;
  virtual const std::map<Tile, int>& getTiles() const = 0;
  virtual bool empty() = 0;

  virtual std::weak_ptr<Agent> getAgent() = 0;
  virtual void setAgent(const std::shared_ptr<Agent>&) = 0;
};

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__PLAYER_H

