/**
 * INTERNAL HEADER, DO NOT INCLUDE EXTERNALLY!!!
 */
#include "Set.h"

#include <memory>

namespace rummikub {
namespace core {

class SetImpl : public Set {
private:
  SetImpl(const SetImpl&) = delete;
  SetImpl& operator=(const SetImpl&) = delete;

private:
  std::unique_ptr<std::vector<Tile>> m_up_tiles;
  mutable bool m_validated;
  mutable Type m_type;

  void validate() const;

public:
  SetImpl();

  void insert(const Tile&);
  bool remove(const Tile&);

  Type getType() const;
  std::vector<Tile> getValidatedTiles() const;
};

} // namespace core
} // namespace rummikub

