#ifndef RUMMIKUB_CORE__TILE_H
#define RUMMIKUB_CORE__TILE_H

#include "CoreFwd.h"

#include <type_traits>

namespace rummikub {
namespace core {

class Tile {
private:
  Tile(const Tile&) = delete;
  const Tile& operator=(const Tile&) = delete;

public:
  enum Color {RED, BLUE, YELLOW, BLACK};
  typedef unsigned char Value;
  static const Value NO_VALUE = -1;
  static const Value MIN_VALUE = 1;
  static const Value MAX_VALUE = 13;

private:
  Color m_color;
  Value m_value;
  bool m_joker;

  Tile(Color, Value, bool) noexcept;

public:
  Tile(Color, Value) noexcept;
  static Tile joker(Color) noexcept;

  Tile(Tile&&) noexcept = default;
  Tile& operator=(Tile&&) noexcept = default;

  Color getColor() const noexcept;
  Value getValue() const noexcept;
  bool isJoker() const noexcept;

  friend bool operator==(const Tile&, const Tile&) noexcept;
  friend bool operator!=(const Tile&, const Tile&) noexcept;
};

static_assert(!std::is_default_constructible<Tile>::value,
              "Tile should NOT be default constructible.");
static_assert(!std::is_copy_constructible<Tile>::value,
              "Tile should NOT be copy constructible.");
static_assert(!std::is_copy_assignable<Tile>::value,
              "Tile should NOT be copy assignable.");
static_assert(std::is_nothrow_move_constructible<Tile>::value,
              "Tile should BE nothrow move constructible.");
static_assert(std::is_nothrow_move_assignable<Tile>::value,
              "Tile should BE nothrow move assignable.");
static_assert(std::is_destructible<Tile>::value,
              "Tile should BE destructible.");

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__TILE_H

