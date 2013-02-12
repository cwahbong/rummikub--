#ifndef RUMMIKUB_CORE__TILE_H
#define RUMMIKUB_CORE__TILE_H

#include "CoreFwd.h"
#include "Util.h"

#include <cctype>
#include <map>
#include <string>
#include <type_traits>

namespace rummikub {
namespace core {

enum Color {
  INVALID,
  RED,
  BLUE,
  YELLOW,
  BLACK,
};

template <typename ValueT, typename NameT, typename Enable = void>
struct ValueTraits {
  MUST_SPECIALIZE(ValueTraits);
};

template <typename ValueT>
struct ValueTraits<ValueT, std::string,
    typename std::enable_if<std::is_integral<ValueT>::value>::type> {
  typedef ValueT ValueType;
  typedef std::string NameType;

  static constexpr bool isInvalid(ValueT v) {return v < MinValue() || MaxValue() < v;}
  static constexpr ValueT MinValue() {return 1;}
  static constexpr ValueT MaxValue() {return 13;}
  static constexpr ValueT JokerValue() {return 100;}
  static constexpr ValueT InvalidValue() {return 110;}
  static constexpr NameType JokerName() {return NameType{"Joker"};}

  static NameType toName(ValueT v) {
    if (v == JokerValue()) {
      return JokerName();
    } else if (!isInvalid(v)) {
      return NameType{std::to_string(v)};
    }
    return NameType{};
  }

  static ValueT toValue(NameType n, size_t* idx = nullptr) {
    size_t idx2{0};
    if (!idx) {
      idx = &idx2;
    }
    while(std::isspace(n[*idx])) ++*idx;
    if (n.find(JokerName(), *idx) == *idx) { // TODO prefix match
      *idx += JokerName().size();
      return JokerValue();
    }
    return _parseValue<ValueT>(n, idx);
  }

private:
  template <typename ValueU>
  static
  typename std::enable_if<std::is_signed<ValueU>::value, ValueU>::type
  _parseValue(NameType n, size_t* p_idx)
  {
    try {
      auto v = stoll(n, p_idx);
      if (isInvalid(v)) {
        return InvalidValue();
      }
      return v;
    } catch (...) {
      return InvalidValue();
    }
  }

  template <typename ValueU>
  static
  typename std::enable_if<std::is_unsigned<ValueU>::value, ValueU>::type
  _parseValue(NameType n, size_t* p_idx)
  {
    try {
      auto v = stoull(n, p_idx);
      if (isInvalid(v)) {
        return InvalidValue();
      }
      return v;
    } catch (...) {
      return InvalidValue();
    }
  }

};

template <typename ColorT, typename NameT, typename Enable = void>
struct ColorTraits {
  MUST_SPECIALIZE(ColorTraits);
};

template <typename NameT>
struct ColorTraits<Color, NameT> {
  typedef Color ColorType;
  typedef NameT NameType;

  static constexpr bool isInvalid(ColorType c) {return c == INVALID;}
  static constexpr ColorType InvalidValue() {return INVALID;}

  static NameType toName(ColorType c) {
    initMap();
    try {
      return m_nameMap.at(c);
    } catch (...) {
      /* Swallow. */
    }
    return NameType{};
  }

  static ColorType toColor(NameType n) {
    initMap();
    try {
      return m_colorMap.at(n);
    } catch (...) {
      /* Swallow. */
    }
    return ColorType{};
  }

private:
  static std::map<ColorType, NameType> m_nameMap;
  static std::map<NameType, ColorType> m_colorMap;

  static void initMap() {
    if (m_nameMap.empty()) {
      addMap(RED,     NameType{"Red"});
      addMap(BLUE,    NameType{"Blue"});
      addMap(YELLOW,  NameType{"Yellow"});
      addMap(BLACK,   NameType{"Black"});
    }
  }

  static void addMap(ColorType c, NameType n) {
    m_nameMap.insert({c, n});
    m_colorMap.insert({n, c});
  }
};

template <typename NameT>
std::map<Color, NameT> ColorTraits<Color, NameT>::m_nameMap;

template <typename NameT>
std::map<NameT, Color> ColorTraits<Color, NameT>::m_colorMap;

template <typename ValueT, typename ColorT, typename NameT = std::string,
    typename VTraits = ValueTraits<ValueT, NameT>,
    typename CTraits = ColorTraits<ColorT, NameT>>
class BasicTile {
public:
  typedef ValueT ValueType;
  typedef VTraits ValueTraitsType;
  typedef ColorT ColorType;
  typedef CTraits ColorTraitsType;
  typedef NameT NameType;

  static const ValueT MIN_VALUE = VTraits::MinValue();
  static const ValueT MAX_VALUE = VTraits::MaxValue();
  static const ValueT JOKER_VALUE = VTraits::JokerValue();

  BasicTile(ColorT c, ValueT v) noexcept
    : m_color{c}, m_value{v}
  {/* Empty. */}

  BasicTile(NameT c, NameT v) noexcept
    : m_color{CTraits::toColor(c)},
      m_value{VTraits::toValue(v)}
  {/* Empty. */}

  static BasicTile joker(ColorT c) noexcept {
    return BasicTile{c, JOKER_VALUE};
  }

  ColorT getColor() const noexcept {
    return m_color;
  }

  NameT getColorName() const noexcept {
    return CTraits::toName(m_color);
  }

  ValueT getValue() const noexcept {
    return m_value;
  }

  NameT getValueName() const noexcept {
    return VTraits::toName(m_value);
  }

  bool isJoker() const noexcept {
    return m_value == JOKER_VALUE;
  }

  friend bool operator< (const BasicTile& lhs, const BasicTile& rhs) noexcept {
    if (lhs.m_color != rhs.m_color) {
      return lhs.m_color < rhs.m_color;
    }
    return lhs.m_value < rhs.m_value;
  }

  friend bool operator==(const BasicTile& lhs, const BasicTile& rhs) noexcept {
    return (lhs.m_color == rhs.m_color) && (lhs.m_value == rhs.m_value);
  }

private:
  ColorT m_color;
  ValueT m_value;
};


template <typename ValueT, typename ColorT, typename NameT,
    typename VTraits, typename CTraits>
const ValueT BasicTile<ValueT, ColorT, NameT, VTraits, CTraits>::MIN_VALUE;

template <typename ValueT, typename ColorT, typename NameT,
    typename VTraits, typename CTraits>
const ValueT BasicTile<ValueT, ColorT, NameT, VTraits, CTraits>::MAX_VALUE;

template <typename ValueT, typename ColorT, typename NameT,
    typename VTraits, typename CTraits>
const ValueT BasicTile<ValueT, ColorT, NameT, VTraits, CTraits>::JOKER_VALUE;

extern template class BasicTile<unsigned, Color>;
typedef BasicTile<unsigned, Color> Tile;

static_assert(!std::is_default_constructible<Tile>::value,
              "Tile should NOT be default constructible.");
static_assert(std::is_copy_constructible<Tile>::value,
              "Tile should BE nothrow copy constructible.");
static_assert(std::is_copy_assignable<Tile>::value,
              "Tile should BE nothrow copy assignable.");
static_assert(std::is_nothrow_move_constructible<Tile>::value,
              "Tile should BE nothrow move constructible.");
static_assert(std::is_nothrow_move_assignable<Tile>::value,
              "Tile should BE nothrow move assignable.");
static_assert(std::is_destructible<Tile>::value,
              "Tile should BE destructible.");

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__TILE_H

