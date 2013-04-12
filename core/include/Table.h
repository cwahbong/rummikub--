#ifndef RUMMIKUB_CORE__TABLE_H
#define RUMMIKUB_CORE__TABLE_H

#include "CoreFwd.h"
#include "StdMemory.h"

#include <vector>

namespace rummikub {
namespace core {

class Table {
public:
  using SetCallback = std::function<void(const s_ptr<Set>&)>;

private:

protected:
  Table& operator=(const Table&) = default;

public:
  Table();
  Table(const Table&);

  static std::shared_ptr<Table> newTable();

  virtual ~Table();

  std::shared_ptr<Table> clone() const;

  void addSet(const std::shared_ptr<const Set>&);
  void clear();
  std::weak_ptr<Set> setRemoveConst(const std::shared_ptr<const Set>&);
  std::vector<std::weak_ptr<const Set>> getSets() const;
  void clean();

  void addInsertSetCallback(const s_ptr<SetCallback>&);
  void addRemoveSetCallback(const s_ptr<SetCallback>&);

  void delInsertSetCallback(const s_ptr<SetCallback>&);
  void delRemoveSetCallback(const s_ptr<SetCallback>&);

private:
  struct Member;
  Member* _;
};

void copyTiles(const std::shared_ptr<Table>& to,
               const std::shared_ptr<const Table>& from);

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__TABLE_H

