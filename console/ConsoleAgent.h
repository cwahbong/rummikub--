#ifndef RUMMIKUB_GAME__CONSOLEAGENT_H
#define RUMMIKUB_GAME__CONSOLEAGENT_H

#include "Agent.h"
#include "CoreFwd.h"

namespace rummikub {

class ConsoleAgent : public Agent {
public:
  virtual void response(const s_ptr<Delegate>& sp_delegate) override;
};

} // namespace rummikub

#endif // RUMMIKUB_GAME__CONSOLEAGENT_H

