#ifndef RUMMIKUB_GAME__CONSOLEAGENT_H
#define RUMMIKUB_GAME__CONSOLEAGENT_H

#include "Agent.h"
#include "CoreFwd.h"

namespace rummikub {
namespace game {

class ConsoleAgent : public core::Agent {
public:
  virtual void response(const s_ptr<core::AgentDelegate>& sp_delegate) override;
};

} // namespace game
} // namespace rummikub

#endif // RUMMIKUB_GAME__CONSOLEAGENT_H

