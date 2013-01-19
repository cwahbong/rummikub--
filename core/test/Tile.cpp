#include "gtest/gtest.h"

#include "Tile.h"

namespace rummikub {
namespace core {

TEST(TileTest, InitTile) {
  Tile joker{Tile::joker(Tile::BLACK)};
  EXPECT_EQ(Tile::BLACK, joker.getColor());
  EXPECT_EQ(Tile::NO_VALUE, joker.getValue());
  EXPECT_TRUE(joker.isJoker());

  Tile t1{Tile::RED, 5};
  EXPECT_EQ(Tile::RED, t1.getColor());
  EXPECT_EQ(5, t1.getValue());
  EXPECT_FALSE(t1.isJoker());
}

} // namespace core
} // namespace rummikub

