#include "gtest/gtest.h"

#include "Tile.h"

namespace rummikub {
namespace core {

TEST(TileTest, InitTile) {
  Tile joker{Tile::joker(BLACK)};
  EXPECT_EQ(BLACK, joker.getColor());
  EXPECT_EQ(Tile::JOKER_VALUE, joker.getValue());
  EXPECT_TRUE(joker.isJoker());

  Tile t1{RED, 5};
  EXPECT_EQ(RED, t1.getColor());
  EXPECT_EQ(5, t1.getValue());
  EXPECT_FALSE(t1.isJoker());
}

} // namespace core
} // namespace rummikub

