#include "gtest/gtest.h"

#include "model/Tile.h"

namespace rummikub {

namespace {

constexpr Tile::Color BLACK = Tile::Color::BLACK;
constexpr Tile::Color RED = Tile::Color::RED;
constexpr Tile::Color YELLOW = Tile::Color::YELLOW;

} // namespace rummikub::<anonymou>

TEST(TileTest, InitTile) {
  Tile joker{Tile::jokerTile(BLACK)};
  EXPECT_EQ(BLACK, joker.getColor());
  EXPECT_EQ(Tile::jokerValue(), joker.getValue());
  EXPECT_TRUE(joker.isJoker());

  Tile t1{RED, 5};
  EXPECT_EQ(RED, t1.getColor());
  EXPECT_EQ(5, t1.getValue());
  EXPECT_FALSE(t1.isJoker());
}

} // namespace rummikub

