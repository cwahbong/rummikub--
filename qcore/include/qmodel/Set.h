#ifndef RUMMIKUB_QCORE__SET_H
#define RUMMIKUB_QCORE__SET_H

#include "CoreFwd.h"
#include "StdMemory.h"
#include "model/Set.h"
#include "model/Tile.h"

#include <QObject>

namespace rummikub {
namespace qmodel {

class Set : public QObject {
  Q_OBJECT
  using Tile = core::Tile;

public:
  explicit Set(core::Set* set, QObject *parent = 0);
  ~Set();

  std::vector<core::Tile> getValidatedTiles() const;

signals:
  void tileInserted(const Tile&);
  void tileRemoved(const Tile&);

private:
  struct Member;
  const u_ptr<Member> _;
};

} // namespace qmodel
} // namespace rummikub

#endif // RUMMIKUB_QCORE__SET_H

