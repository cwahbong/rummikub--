#ifndef RUMMIKUB_CORE__TABLE_H
#define RUMMIKUB_CORE__TABLE_H

#include "CoreFwd.h"
#include "StdMemory.h"

#include <vector>

namespace rummikub {

class Table {
  Table(Table&&) = delete;
  Table& operator=(Table&&) = delete;

public:
  Table();
  Table(const Table&);
  Table& operator=(const Table&);
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

} // namespace rummikub

#endif // RUMMIKUB_CORE__TABLE_H

