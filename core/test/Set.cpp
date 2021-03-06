#include "gtest/gtest.h"

#include "model/Set.h"
#include "model/Tile.h"

using std::make_shared;

namespace rummikub {

namespace {

constexpr Tile::Color BLACK = Tile::Color::BLACK;
constexpr Tile::Color RED = Tile::Color::RED;
constexpr Tile::Color YELLOW = Tile::Color::YELLOW;

} // namespace rummikub::<anonymous>

TEST(SetTest, ValidateRun) {
  const auto& sp_set = make_shared<Set>();
  sp_set->insert(Tile{RED, 5});
  sp_set->insert(Tile{RED, 6});
  sp_set->insert(Tile{RED, 7});
  EXPECT_EQ(Set::RUN, sp_set->getType());
}

TEST(SetTest, ValidateRunWithJokers) {
  const auto& sp_set = make_shared<Set>();
  sp_set->insert(Tile{RED, 5});
  sp_set->insert(Tile{RED, 6});
  sp_set->insert(Tile::jokerTile(BLACK));
  sp_set->insert(Tile::jokerTile(BLACK));
  sp_set->insert(Tile{RED, 8});
  sp_set->insert(Tile{RED, 10});
  sp_set->insert(Tile{RED, 7});
  EXPECT_EQ(Set::RUN, sp_set->getType());
}

TEST(SetTest, ValidateGroup) {
  const auto& sp_set = make_shared<Set>();
  sp_set->insert(Tile{RED, 5});
  sp_set->insert(Tile{BLACK, 5});
  sp_set->insert(Tile{YELLOW, 5});
  EXPECT_EQ(Set::GROUP, sp_set->getType());
}

TEST(SetTest, ValidateGroupWithJokers) {
  const auto& sp_set = make_shared<Set>();
  sp_set->insert(Tile{RED, 5});
  sp_set->insert(Tile{BLACK, 5});
  sp_set->insert(Tile::jokerTile(BLACK));
  sp_set->insert(Tile::jokerTile(BLACK));
  EXPECT_EQ(Set::GROUP, sp_set->getType());
}

TEST(SetTest, ValidateNoneRun) {
  const auto& sp_set = make_shared<Set>();
  sp_set->insert(Tile{RED, 5});
  sp_set->insert(Tile{RED, 6});
  sp_set->insert(Tile{BLACK, 7});
  EXPECT_EQ(Set::NONE, sp_set->getType());
}

TEST(SetTest, ValidateNoneGroup) {
  const auto& sp_set = make_shared<Set>();
  sp_set->insert(Tile{RED, 5});
  sp_set->insert(Tile{RED, 5});
  sp_set->insert(Tile{BLACK, 5});
  sp_set->insert(Tile{YELLOW, 5});
  EXPECT_EQ(Set::NONE, sp_set->getType());
}

TEST(SetTest, ValidateNoneGroupWithJokers) {
  const auto& sp_set = make_shared<Set>();
  sp_set->insert(Tile{RED, 5});
  sp_set->insert(Tile{BLACK, 5});
  sp_set->insert(Tile{YELLOW, 5});
  sp_set->insert(Tile::jokerTile(BLACK));
  sp_set->insert(Tile::jokerTile(RED));
  EXPECT_EQ(Set::NONE, sp_set->getType());
}

} // namespace rummikub


