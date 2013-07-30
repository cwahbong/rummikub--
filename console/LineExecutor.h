#ifndef RUMMIKUB_CONSOLE__LINEEXECUTOR_H
#define RUMMIKUB_CONSOLE__LINEEXECUTOR_H

#include "Agent.h"
#include "StdMemory.h"

#include <functional>
#include <string>

namespace rummikub {

using LineExecutor = std::function<bool(const std::string&, const s_ptr<Agent::Delegate>&)>;

LineExecutor defaultLineExecutor();

} // namespace rummikub

#endif // RUMMIKUB_CONSOLE__LINEEXECUTOR_H
