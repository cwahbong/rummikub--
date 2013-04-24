#ifndef RUMMIKUB_CORE__STDMEMORY_H
#define RUMMIKUB_CORE__STDMEMORY_H

#include <memory>

namespace rummikub {

template <typename T> using  w_ptr = std::weak_ptr<T>;
template <typename T> using cw_ptr = std::weak_ptr<const T>;
template <typename T> using  u_ptr = std::unique_ptr<T>;
template <typename T> using cu_ptr = std::unique_ptr<const T>;
template <typename T> using  s_ptr = std::shared_ptr<T>;
template <typename T> using cs_ptr = std::shared_ptr<const T>;

} // namespace rummikub

#endif // RUMMIKUB_CORE__STDMEMORY_H

