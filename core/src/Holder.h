#ifndef RUMMIKUB_CORE__HOLDER_H
#define RUMMIKUB_CORE__HOLDER_H

#include "CoreFwd.h"

#include <algorithm>
#include <iterator>
#include <map>
#include <vector>
#include <utility>

namespace rummikub {
namespace core {

template <typename ValueT, typename CounterT = size_t,
    typename KindContainerT = std::vector<ValueT>>
class Holder {
public:
  using CounterType = CounterT;
  using ValueType = ValueT;
  using KindContainerType = KindContainerT;

  void
  add(const ValueT& v, CounterT c = 1)
  {
    if (c <= 0) return;
    m_map[v] = (has(v) ? m_map[v] + c : c);
  }

  bool
  remove(const ValueT& v, CounterT c = 1)
  {
    if (c <= 0) return true;
    if (!has(v)) return false;
    if (m_map[v] < c) return false;
    if (m_map[v] == c) {
      m_map.erase(v);
    } else {
      m_map[v] -= c;
    }
    return true;
  }

  void clear()
  {
    m_map.clear();
  }

  bool
  empty() const
  {
    return m_map.empty();
  }

  bool
  has(const ValueT& v) const
  {
    return m_map.find(v) != m_map.end();
  }

  CounterT
  count(const ValueT& v) const
  {
    return has(v) ? m_map.at(v) : 0;
  }

  KindContainerT
  kinds() const
  {
    KindContainerT result{};
    std::transform(m_map.begin(), m_map.end(),
        std::back_inserter(result),
        [](const std::pair<ValueT, CounterT>& p) {
            return p.first;
        }
    );
    return result;
  }

private:
  std::map<ValueT, CounterT> m_map;
};

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__HOLDER_H

