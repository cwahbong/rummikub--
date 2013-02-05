/**
 * INTERNAL HEADER, DO NOT INCLUDE EXTERNALLY!!!
 */
#include "Set.h"

#include "Tile.h"

using std::vector;
using std::shared_ptr;

namespace rummikub {
namespace core {

class SetImpl : public Set {
private:
  SetImpl& operator=(const SetImpl&) = delete;

private:
  mutable vector<Tile> m_tiles;
  mutable bool m_validated;
  mutable Type m_type;

  void validate() const;

public:
  SetImpl();

  SetImpl(const SetImpl&) = default;
  SetImpl(SetImpl&&) = default;
  SetImpl& operator=(SetImpl&&) = default;

  shared_ptr<Set> clone() const;

  void insert(const Tile&);
  bool remove(const Tile&);
  bool empty() const;

  Type getType() const;
  vector<Tile> getValidatedTiles() const;
};

} // namespace core
} // namespace rummikub

