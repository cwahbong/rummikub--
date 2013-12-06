#include "model/Tile.h"
  using Color = rummikub::Tile::Color;
  using Value = rummikub::Tile::Value;

#include <string>
  using std::string;

namespace rummikub {

// static
string
Tile::to_string(const Color& c)
{
  switch (c) {
  case Color::RED:
    return "red";
  case Color::BLUE:
    return "blue";
  case Color::YELLOW:
    return "yellow";
  case Color::BLACK:
    return "black";
  default:
    return "invalid";
  }
}

// static
string
Tile::to_string_short(const Color& c)
{
  switch (c) {
  case Color::RED:
    return "R";
  case Color::BLUE:
    return "B";
  case Color::YELLOW:
    return "Y";
  case Color::BLACK:
    return "X";
  default:
    return ".";
  }
}

// static
string
Tile::to_string(const Value& v)
{
  return std::to_string(v);
}

Tile::Tile()
  : Tile(INVALID, 0)
{/* Empty. */}

Tile::Tile(const Color& c, const Value& v)
  : _c{c}, _v{v}
{/* Empty. */}

void
Tile::setColor(const Color& c)
{
  _c = c;
}

Color
Tile::getColor() const
{
  return _c;
}

void
Tile::setValue(const Value& v)
{
  _v = v;
}

Value
Tile::getValue() const
{
  return _v;
}

bool
Tile::isJoker() const
{
  return _v == jokerValue();
}

bool
operator< (const Tile& lhs, const Tile& rhs) {
  if (lhs._c != rhs._c) {
    return lhs._c < rhs._c;
  }
  return lhs._v < rhs._v;
}

bool
operator==(const Tile& lhs, const Tile& rhs) {
  return (lhs._c == rhs._c) && (lhs._v == rhs._v);
}


// static
Value
Tile::jokerValue()
{
  return 100;
}

// static
Tile
Tile::jokerTile(const Color& c)
{
  return Tile{c, jokerValue()};
}

} // namespace rummikub

