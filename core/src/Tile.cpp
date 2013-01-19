#include "Tile.h"

namespace rummikub {
namespace core {

// We still need definition here, see DR 712 for more detail.
// http://gcc.gnu.org/wiki/VerboseDiagnostics#missing_static_const_definition
const Tile::Value Tile::NO_VALUE;
const Tile::Value Tile::MIN_VALUE;
const Tile::Value Tile::MAX_VALUE;

Tile::Tile(Color color, Value value, bool joker) noexcept
  : m_color(color),
    m_value(value),
    m_joker(joker)
{/* Empty. */}

Tile::Tile(Color color, Value value) noexcept
  : Tile(color, value, false)
{/* Empty. */}

Tile
Tile::joker(Color color) noexcept
{
  return Tile{color, NO_VALUE, true};
}

Tile::Color
Tile::getColor() const noexcept
{
  return m_color;
}

Tile::Value
Tile::getValue() const noexcept
{
  return m_value;
}

bool
Tile::isJoker() const noexcept
{
  return m_joker;
}

bool
operator==(const Tile& lhs, const Tile& rhs) noexcept
{
  return (lhs.m_color == rhs.m_color) && (lhs.m_value == rhs.m_value);
}

inline
bool
operator!=(const Tile& lhs, const Tile& rhs) noexcept
{
  return ! (lhs == rhs);
}

} // namespace core
} // namespace rummikub

