#ifndef RUMMIKUB_CORE__SET_H
#define RUMMIKUB_CORE__SET_H

#include "CoreFwd.h"

#include <memory>
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

  Set(Set&&) = default;
  Set& operator=(Set&&) = default;

public:
  virtual ~Set() noexcept = default;

  static std::shared_ptr<Set> newSet();

  virtual void insert(const Tile&) = 0;
  virtual bool remove(const Tile&) = 0;
  virtual bool empty() const = 0;

  virtual Type getType() const = 0;
  virtual std::vector<Tile> getValidatedTiles() const = 0;
};

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__SET_H

