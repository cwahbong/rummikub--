#ifndef RUMMIKUB_CONSOLE__STREAMCOORDINATOR_H
#define RUMMIKUB_CONSOLE__STREAMCOORDINATOR_H

#include "Agent.h"
#include "EventReceiver.h"
#include "StdMemory.h"

#include <istream>
#include <ostream>

namespace rummikub {

class StreamCoordinator : public Agent, public EventReceiver
{
public:
  StreamCoordinator(std::istream&, std::ostream&);
  ~StreamCoordinator();

  void response(const s_ptr<Delegate>&) const override;

  void tilePut(const cs_ptr<Player>&, const Tile& tile, const cs_ptr<Set>&) override;

private:
  struct Member;
  const u_ptr<Member> _;
};

} // namespace rummikub

#endif // RUMMIKUB_CONSOLE__STREAMCOORDINATOR_H

