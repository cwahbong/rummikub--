#ifndef RUMMIKUB_CORE__CORE_FWD_H
#define RUMMIKUB_CORE__CORE_FWD_H

#include <string>

namespace rummikub {
namespace core {

enum Color : int;

template <typename ValueT, typename NameT, typename Enable = void> class ValueTraits;

template <typename ColorT, typename NameT, typename Enable = void> class ColorTraits;

template <typename ValueT, typename ColorT, typename NameT = std::string,
    typename VTraits = ValueTraits<ValueT, NameT>,
    typename CTraits = ColorTraits<ColorT, NameT>>
class BasicTile;

typedef BasicTile<unsigned, Color> Tile;

class Agent;
class AgentDelegate;
class Component;
class Player;
class Set;
class Table;
class TileManager;
class Rummikub;

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__CORE_FWD_H

