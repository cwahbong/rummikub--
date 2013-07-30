#include "OutputFormatter.h"

#include "model/Hand.h"
#include "model/Set.h"
#include "model/Table.h"
#include "model/Tile.h"

#include <utility>

using std::make_shared;
using std::move;
using std::string;
using std::to_string;

namespace rummikub {

namespace {

string
to_string_short(const Color& color) {
  switch (color) {
  case RED:
    return "R";
  case BLUE:
    return "B";
  case YELLOW:
    return "Y";
  case BLACK:
    return "X";
  }
  return ".";
}

} // namespace

struct OutputFormatter::Member {
  TileF tileF;
  SetF setF;
  HandF handF;
  TableF tableF;
};

OutputFormatter::OutputFormatter(
    const TileF& tileF,
    const SetF& setF,
    const HandF& handF,
    const TableF& tableF)
  : _{new Member{tileF, setF, handF, tableF}}
{/* Empty. */}

OutputFormatter::OutputFormatter(OutputFormatter&& outputFormatter)
  : _{move(outputFormatter._)}
{/* Empty. */}

OutputFormatter::~OutputFormatter()
{/* Empty. */}

string
OutputFormatter::format(const Tile& tile) const
{
  return _->tileF(*this, tile);
}

string
OutputFormatter::format(const cs_ptr<Set>& sp_set) const
{
  return _->setF(*this, sp_set);
}

string
OutputFormatter::format(const cs_ptr<Hand>& sp_hand) const
{
  return _->handF(*this, sp_hand);
}

string
OutputFormatter::format(const cs_ptr<Table>& sp_table) const
{
  return _->tableF(*this, sp_table);
}

OutputFormatter::TileF
defaultTileF()
{
  return [](const OutputFormatter&, const Tile& tile) {
    return to_string_short(tile.getColor())
         + "-"
         + to_string(tile.getValue());
  };
}

OutputFormatter::SetF
defaultSetF()
{
  return [](const OutputFormatter& formatter, const cs_ptr<Set>& sp_set) {
    string result;
    for (const auto& tile : sp_set->getValidatedTiles()) {
      result += formatter.format(tile) + " ";
    }
    return result;
  };
}

OutputFormatter::HandF
defaultHandF()
{
  return [](const OutputFormatter& formatter, const cs_ptr<Hand>& sp_hand) {
    string result;
    const auto& kinds = sp_hand->getKinds();
    for (decltype(sp_hand->getKinds())::size_type i = 0, maxi = kinds.size(); i < maxi; ++i) {
      if ((i > 0) && (i % 5 == 0)) {
        result += "\n";
      }
      const auto& tile = kinds[i];
      result += "<" + to_string(i) + ">" + formatter.format(tile);
      auto count = sp_hand->count(tile);
      if (count > 1) {
        result += "x";
        result += to_string(count);
      }
      result += " ";
    }
    result += "\n";
    return result;
  };
}

OutputFormatter::TableF
defaultTableF()
{
  return [](const OutputFormatter& formatter, const cs_ptr<Table>& sp_table) {
    string result;
    for (const auto& wp_set : sp_table->getSets()) {
      result += formatter.format(wp_set.lock()) + "\n";
    }
    return result;
  };
}

OutputFormatter
defaultOutputFormatter()
{
  return OutputFormatter{
      defaultTileF(),
      defaultSetF(),
      defaultHandF(),
      defaultTableF()
  };
}

} // namespace rummikub

