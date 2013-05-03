#ifndef RUMMIKUB_QCORE__SET_H
#define RUMMIKUB_QCORE__SET_H

#include "Fwd.h"

#include "CoreFwd.h"
#include "StdMemory.h"
#include "model/Set.h"

#include <QObject>

namespace rummikub {
namespace qmodel {

class Set : public QObject {
  Q_OBJECT

public:
  explicit Set(const s_ptr<core::Set>&, QObject *parent = 0);
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

