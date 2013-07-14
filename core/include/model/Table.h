#ifndef RUMMIKUB_CORE__TABLE_H
#define RUMMIKUB_CORE__TABLE_H

#include "CoreFwd.h"
#include "StdMemory.h"

#include <vector>

namespace rummikub {

class Table {
protected:
  Table& operator=(const Table&) = default;

public:
  explicit Table();
  Table(const Table&);
  ~Table();

  s_ptr<Set> addSet();
  s_ptr<Set> addSet(const cs_ptr<Set>&);

  void clear();
  std::vector<cw_ptr<Set>> getSets() const;
  void clean();

private:
  struct Member;
  const u_ptr<Member> _;
};

void copyTiles(const std::shared_ptr<Table>& to,
               const std::shared_ptr<const Table>& from);

} // namespace rummikub

#endif // RUMMIKUB_CORE__TABLE_H

