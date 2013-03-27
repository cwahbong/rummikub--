#include "Component.h"

#include "Rummikub.h"

using std::weak_ptr;
using std::shared_ptr;

namespace rummikub {
namespace core {

struct Component::Member {
  Rummikub* rummikub;
};

Component::Component(Rummikub* rummikub)
  : _{new Member{rummikub}}
{}

Component::~Component()
{
  delete _;
}

Rummikub*
Component::getRummikub()
{
  return _->rummikub;
}

} // namespace core
} // namespace rummikub

