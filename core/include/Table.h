#ifndef RUMMIKUB_CORE__TABLE_H
#define RUMMIKUB_CORE__TABLE_H

#include "CoreFwd.h"

#include <memory>
#include <set>
#include <vector>

namespace rummikub {
namespace core {

class Table {
protected:
  Table() = default;
  Table(const Table&) = default;
  Table& operator=(const Table&) = default;

public:
  static std::shared_ptr<Table> newTable();

  virtual ~Table() = default;

  virtual std::shared_ptr<Table> clone() const = 0;

  virtual void addSet(const std::shared_ptr<const Set>&) = 0;
  virtual void clear() = 0;
  virtual std::weak_ptr<Set> setRemoveConst(const std::shared_ptr<const Set>&) = 0;
  virtual std::vector<std::weak_ptr<const Set>> getSets() const = 0;
  virtual void clean() = 0;
};

void copyTiles(const std::shared_ptr<Table>& to,
               const std::shared_ptr<const Table>& from);

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__TABLE_H

