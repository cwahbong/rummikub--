/**
 * INTERNAL HEADER, DO NOT INCLUDE EXTERNALLY!!!
 */
#include "Set.h"

#include "Tile.h"

#include <memory>

using std::unique_ptr;
using std::vector;

namespace rummikub {
namespace core {

class SetImpl : public Set {
private:
  SetImpl(const SetImpl&) = delete;
  SetImpl& operator=(const SetImpl&) = delete;

private:
  mutable vector<Tile> m_tiles;
  mutable bool m_validated;
  mutable Type m_type;

  void validate() const;

public:
  SetImpl();

  SetImpl(SetImpl&&) = default;
  SetImpl& operator=(SetImpl&&) = default;

  void insert(const Tile&);
  bool remove(const Tile&);

  Type getType() const;
  vector<Tile> getValidatedTiles() const;
};

} // namespace core
} // namespace rummikub

