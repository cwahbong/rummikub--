#ifndef RUMMIKUB_CORE__CORE_FWD_H
#define RUMMIKUB_CORE__CORE_FWD_H

#include <string>

namespace rummikub {

enum Color : int;

template <typename ValueT, typename NameT, typename Enable = void> class ValueTraits;

template <typename ColorT, typename NameT, typename Enable = void> class ColorTraits;

template <typename ValueT, typename ColorT, typename NameT = std::string,
    typename VTraits = ValueTraits<ValueT, NameT>,
    typename CTraits = ColorTraits<ColorT, NameT>>
class BasicTile;

typedef BasicTile<unsigned, Color> Tile;

class Agent;
class EventReceiver;
class Hand;
class Set;
class Table;
class Rummikub;

} // namespace rummikub

#endif // RUMMIKUB_CORE__CORE_FWD_H

