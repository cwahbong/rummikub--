#ifndef RUMMIKUB_CORE__SET_H
#define RUMMIKUB_CORE__SET_H

#include "CoreFwd.h"
#include "Component.h"

#include <vector>

namespace rummikub {
namespace core {

class Set : Component {
public:
  enum Type {RUN, GROUP, NONE};

protected:
  Set(Set&&) = default;
  Set& operator=(Set&&) = default;
  void validate() const;

public:
  Set(Rummikub* rummikub = nullptr);
  virtual ~Set();

  Set(const Set&);
  Set& operator=(const Set&) = delete;

  void insert(const Tile&);
  bool remove(const Tile&);
  bool empty() const;

  Type getType() const;
  std::vector<Tile> getValidatedTiles() const;

private:
  struct Member;
  Member* _;
};

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__SET_H

