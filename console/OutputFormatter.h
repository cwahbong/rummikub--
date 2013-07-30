#ifndef RUMMIKUB_CONSOLE__OUTPUTFORMATTER_H
#define RUMMIKUB_CONSOLE__OUTPUTFORMATTER_H

#include "CoreFwd.h"
#include "StdMemory.h"

#include <functional>
#include <string>

namespace rummikub {

class OutputFormatter final
{
public:
  using TileF  = std::function<std::string(const OutputFormatter&, const Tile&)>;
  using SetF   = std::function<std::string(const OutputFormatter&, const cs_ptr<Set>&)>;
  using HandF  = std::function<std::string(const OutputFormatter&, const cs_ptr<Hand>&)>;
  using TableF = std::function<std::string(const OutputFormatter&, const cs_ptr<Table>&)>;

  OutputFormatter(const TileF& tileF,
                  const SetF& setF,
                  const HandF& handF,
                  const TableF& tableF);
  OutputFormatter(OutputFormatter&&);
  ~OutputFormatter();

  std::string format(const Tile&) const;
  std::string format(const cs_ptr<Set>&) const;
  std::string format(const cs_ptr<Hand>&) const;
  std::string format(const cs_ptr<Table>&) const;

private:
  struct Member;
  u_ptr<Member> _;
};

OutputFormatter::TileF defaultTileF();
OutputFormatter::SetF defaultSetF();
OutputFormatter::HandF defaultHandF();
OutputFormatter::TableF defaultTableF();

OutputFormatter defaultOutputFormatter();

} // namespace rummikub

#endif // RUMMIKUC_CONSOLE__OUTPUTFORMATTER_H
