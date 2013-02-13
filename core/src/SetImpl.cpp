#include "SetImpl.h"

#include "Tile.h"

#include <iostream>
#include <algorithm>
#include <array>

using std::array;
using std::find;
using std::sort;
using std::vector;

namespace rummikub {
namespace core {

namespace {

template <typename RandomAccessContainer>
Set::Type
validate(RandomAccessContainer& tiles)
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

shared_ptr<Set>
SetImpl::clone() const
{
  return shared_ptr<Set>{new SetImpl{*this}};
}

SetImpl::SetImpl()
  : m_tiles(),
    m_validated(false),
    m_type(NONE)
{/* Empty. */}

void
SetImpl::validate() const
{
  m_type = ::rummikub::core::validate(m_tiles);
  m_validated = true;
}

void
SetImpl::insert(const Tile& tile)
{
  m_validated = false;
  m_tiles.push_back(tile);
}

bool
SetImpl::remove(const Tile& tile)
{
  auto it = find(m_tiles.begin(), m_tiles.end(), tile);
  if (it != m_tiles.end()) {
    m_tiles.erase(it);
    m_validated = false;
    return true;
  }
  return false;
}

bool
SetImpl::empty() const
{
  return m_tiles.empty();
}

Set::Type
SetImpl::getType() const
{
  if (!m_validated) {
    validate();
  }
  return m_type;
}

vector<Tile>
SetImpl::getValidatedTiles() const
{
  if (!m_validated) {
    validate();
  }
  return vector<Tile>{m_tiles.begin(), m_tiles.end()};
}

} // namespace core
} // namespace rummikub

