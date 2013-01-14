#include "Set.h"
#include "SetImpl.h"

namespace rummikub {
namespace core {

Set*
Set::newSet()
{
  return new SetImpl();
}

} // namespace core
} // namespace rummikub

