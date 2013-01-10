#include "Tile.h"

namespace rummikub {
namespace core {

Tile::Tile(Color color, Value value)
  : m_color(color), m_value (value)
{/* Empty. */}

Tile::Color
Tile::getColor() const
{
  return m_color;
}

Tile::Value
Tile::getValue() const
{
  return m_value;
}

} // namespace core
} // namespace rummikub

