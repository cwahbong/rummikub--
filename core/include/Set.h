#ifndef RUMMIKUB_CORE__SET_H
#define RUMMIKUB_CORE__SET_H

#include "CoreFwd.h"

#include <vector>

namespace rummikub {
namespace core {

class Set {
private:
  Set(const Set&) = delete;
  Set& operator=(const Set&) = delete;

public:
  enum Type {RUN, GROUP, NONE};

protected:
  Set() = default;

public:
  virtual ~Set() = default;

  static Set* newSet();

  virtual void insert(const Tile&) = 0;
  virtual bool remove(const Tile&) = 0;

  virtual Type getType() const = 0;
  virtual std::vector<Tile> getValidatedTiles() const = 0;
};

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__SET_H

