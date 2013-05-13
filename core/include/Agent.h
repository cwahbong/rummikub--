#ifndef RUMMIKUB_CORE__AGENT_H
#define RUMMIKUB_CORE__AGENT_H

#include "CoreFwd.h"

#include "StdMemory.h"

namespace rummikub {
namespace core {

/**
 */
class Agent {
public:
  virtual void response(const s_ptr<AgentDelegate>&) = 0;
};

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__AGENT_H

