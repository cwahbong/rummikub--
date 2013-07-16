#ifndef RUMMIKUB_CORE__SET_H
#define RUMMIKUB_CORE__SET_H

#include "CoreFwd.h"
#include "StdMemory.h"

#include <vector>

namespace rummikub {

class Set {
  Set(Set&&) = delete;
  Set& operator=(Set&&) = delete;

public:
  enum Type {RUN, GROUP, NONE};

protected:
  void validate() const;

public:
  Set();
  Set(const Set&);
  Set& operator=(const Set&);
  ~Set();

  void insert(const Tile&);
  bool remove(const Tile&);
  bool empty() const;

  Type getType() const;
  std::vector<Tile> getValidatedTiles() const;

private:
  struct Member;
  const u_ptr<Member> _;
};

} // namespace rummikub

#endif // RUMMIKUB_CORE__SET_H

