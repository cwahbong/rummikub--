#ifndef RUMMIKUB_CORE__COMPONENT_H
#define RUMMIKUB_CORE__COMPONENT_H

#include "CoreFwd.h"

namespace rummikub {
namespace core {

class Component {
public:
  Component(Rummikub* rummikub);
  virtual ~Component();

  Rummikub* getRummikub();

private:
  struct Member;
  Member* _;
};

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__COMPONENT_H

