#ifndef RUMMIKUB_CORE__SET_H
#define RUMMIKUB_CORE__SET_H

#include "CoreFwd.h"
#include "Component.h"
#include "Util.h"

#include <memory>
#include <vector>

namespace rummikub {
namespace core {


class Set : Component {
public:
  enum Type {RUN, GROUP, NONE};
  enum Message {INSERT, REMOVE, DELETE};

protected:
  Set(const Set&) = default;
  Set& operator=(const Set&) = default;
  Set(Set&&) = default;
  Set& operator=(Set&&) = default;
  void validate() const;

public:
  Set(Rummikub* rummikub = nullptr);
  virtual ~Set();

  static std::shared_ptr<Set> newSet();

  virtual std::shared_ptr<Set> clone() const;

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

