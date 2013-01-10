#ifndef RUMMIKUB_CORE__TILE_H
#define RUMMIKUB_CORE__TILE_H

namespace rummikub {
namespace core {

class Tile {
private:
  Tile(const Tile&);
  Tile& operator=(const Tile&);

public:
  enum Color {RED, BLUE, YELLOW, BLACK};
  typedef unsigned char Value;

private:
  Color m_color;
  Value m_value;

public:
  Tile(Color, Value);

  Color getColor() const;
  Value getValue() const;
};

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__TILE_H

