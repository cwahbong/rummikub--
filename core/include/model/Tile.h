#ifndef RUMMIKUB_CORE__TILE_H
#define RUMMIKUB_CORE__TILE_H

#include "CoreFwd.h"
#include "Util.h"

#include <cctype>
#include <map>
#include <string>
#include <type_traits>

namespace rummikub {


class Tile {
public:
  enum Color : int {
    INVALID = -1,
    RED,
    BLUE,
    YELLOW,
    BLACK,
  };
  using Value = unsigned;

  static std::string to_string(const Color&);
  static std::string to_string_short(const Color&);
  static std::string to_string(const Value&);

  Tile(const Color& c, const Value& v);

  void setColor(const Color&);
  Color getColor() const;

  void setValue(const Value&);
  Value getValue() const;

  bool isJoker() const;
  bool isValid() const;

  friend bool operator< (const Tile&, const Tile&);
  friend bool operator==(const Tile&, const Tile&);

  static constexpr Value minValue() {return 1;}
  static constexpr Value maxValue() {return 13;}
  static Value jokerValue();

  static Tile jokerTile(const Color& c);

private:
  Color _c;
  Value _v;
};

} // namespace rummikub

#endif // RUMMIKUB_CORE__TILE_H

