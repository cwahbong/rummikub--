#include "Set.h"

#include "Tile.h"
#include "Rummikub.h"

#include <array>
#include <vector>

using std::array;
using std::shared_ptr;
using std::vector;

namespace rummikub {
namespace core {

namespace {

template <typename RandomAccessContainer>
Set::Type
validateTiles(RandomAccessContainer& tiles)
{
  if (tiles.size() < 3) {
    return Set::NONE;
  }
  array<int, 14> valueCount{};
  array<int, 5> colorCount{};
  Tile::ValueType minValue{Tile::MAX_VALUE};
  Tile::ValueType maxValue{Tile::MIN_VALUE};
  int jokerCount{};
  for (const auto& tile : tiles) {
    if (tile.isJoker()) {
      ++jokerCount;
    } else {
      ++valueCount[tile.getValue()];
      ++colorCount[tile.getColor()];
      minValue = std::min(minValue, tile.getValue());
      maxValue = std::max(maxValue, tile.getValue());
    }
  }
  // validate run
  int colorKind{};
  int zeroChance = jokerCount;
  for (const auto& color : colorCount) {
    if (color > 0) {
      ++colorKind;
    }
  }
  for (auto v = minValue; v<=maxValue && zeroChance>=0; ++v) {
    if (valueCount[v] > 1) {
      zeroChance = -1;
    } else if (valueCount[v] == 0) {
      --zeroChance;
    }
  }
  if (zeroChance >= 0 && colorKind == 1) {
    sort(tiles.begin(), tiles.end(), [](const Tile& lhs, const Tile& rhs) {
        return lhs.getValue() < rhs.getValue();
    });
    return Set::RUN;
  }
  // validate group
  int valueKind{};
  bool threeUp{};
  for (const auto& count : valueCount) {
    if (count) {
      ++valueKind;
    }
    if (count + jokerCount == 3 || count + jokerCount == 4) {
      threeUp = true;
    }
  }
  for (const auto& count : colorCount) {
    if (count > 1) {
      return Set::NONE;
    }
  }
  if (valueKind == 1 && threeUp) {
    sort(tiles.begin(), tiles.end(), [](const Tile& lhs, const Tile& rhs) {
         return lhs.getColor() < rhs.getColor();
    });
    return Set::GROUP;
  }
  return Set::NONE;
}

} // namespace

struct Set::Member
{
  mutable vector<Tile> tiles;
  mutable bool validated;
  mutable Type type;
};

Set::Set(Rummikub* rummikub)
  : Component{rummikub},
    _{new Member{{}, false, NONE}}
{/* Empty. */}

Set::Set(const Set& set)
  : Component{set.getRummikub()},
    _{new Member(*set._)}
{/* Empty. */}

Set::~Set()
{
  delete _;
}

void
Set::validate() const
{
  _->type = validateTiles(_->tiles);
  _->validated = true;
}

void
Set::insert(const Tile& tile)
{
  _->validated = false;
  _->tiles.push_back(tile);
  // getRummikub()->getNotifier()->notify<SET_INSERT>(tile);
}

bool
Set::remove(const Tile& tile)
{
  auto it = find(_->tiles.begin(), _->tiles.end(), tile);
  if (it != _->tiles.end()) {
    _->tiles.erase(it);
    _->validated = false;
    // getRummikub()->getNotifier()->notify<SET_REMOVE>(tile);
    return true;
  }
  return false;
}

bool
Set::empty() const
{
  return _->tiles.empty();
}

Set::Type
Set::getType() const
{
  if (!_->validated) {
    validate();
  }
  return _->type;
}

vector<Tile>
Set::getValidatedTiles() const
{
  if (!_->validated) {
    validate();
  }
  return vector<Tile>{_->tiles.begin(), _->tiles.end()};
}

} // namespace core
} // namespace rummikub

