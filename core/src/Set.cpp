#include "Set.h"
#include "SetImpl.h"

using std::dynamic_pointer_cast;
using std::make_shared;
using std::shared_ptr;

namespace rummikub {
namespace core {

shared_ptr<Set>
Set::newSet()
{
  return shared_ptr<Set>{new SetImpl{}};
}

} // namespace core
} // namespace rummikub

