#ifndef RUMMIKUB_CORE__TABLE_H
#define RUMMIKUB_CORE__TABLE_H

#include "CoreFwd.h"

#include <memory>
#include <set>
#include <vector>

namespace rummikub {
namespace core {

class Table {
private:
  Table(const Table&) = delete;
  Table& operator=(const Table&) = delete;

protected:
  Table() = default;

public:
  static std::shared_ptr<Table> newTable();

  virtual ~Table() = default;

  virtual void addSet(const std::shared_ptr<Set>&) = 0;
  virtual std::weak_ptr<Set> setRemoveConst(const std::shared_ptr<const Set>&) = 0;
  virtual std::vector<std::weak_ptr<const Set>> getSets() const = 0;
  virtual void clean() = 0;
};

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__TABLE_H

