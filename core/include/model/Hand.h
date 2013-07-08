#ifndef RUMMIKUB_CORE__HAND_H
#define RUMMIKUB_CORE__HAND_H

#include "CoreFwd.h"
#include "StdMemory.h"

#include <vector>

namespace rummikub {

class Hand {
protected:
  Hand& operator=(const Hand&) = default;
  Hand(Hand&&) = default;
  Hand& operator=(Hand&&) = default;

public:
  Hand();
  Hand(const Hand&);
  ~Hand();

  void addTile(const Tile& tile, size_t count = 1);
  bool removeTile(const Tile& tile, size_t count = 1);
  void clearTiles();
  bool hasTile(const Tile& tile) const;
  size_t count(const Tile& tile) const;
  std::vector<Tile> getKinds() const;
  bool empty() const;

private:
  struct Member;
  const u_ptr<Member> _;
};

void copyTiles(const std::shared_ptr<Hand>& to,
               const std::shared_ptr<const Hand>& from);

} // namespace rummikub

#endif // RUMMIKUB_CORE__HAND_H

