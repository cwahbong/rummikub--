#ifndef RUMMIKUB_CORE__STDMEMORY_H
#define RUMMIKUB_CORE__STDMEMORY_H

#include <memory>
#include <utility>

/*! \file
 *  \brief Smart pointer types and functions.
 *
 *  TODO: let user to use their own smart pointer type.
 */

namespace rummikub {

/*! \addtogroup rummicore
 *  @{
 */

/*! \brief Weak pointer type. */
template <typename T> using  w_ptr = std::weak_ptr<T>;
/*! \brief Weak pointer type pointing to const. */
template <typename T> using cw_ptr = std::weak_ptr<const T>;
/*! \brief Unique pointer type. */
template <typename T> using  u_ptr = std::unique_ptr<T>;
/*! \brief Unique pointer type pointing to const. */
template <typename T> using cu_ptr = std::unique_ptr<const T>;
/*! \brief Shared pointer type. */
template <typename T> using  s_ptr = std::shared_ptr<T>;
/*! \brief Shared pointer type pointing to const */
template <typename T> using cs_ptr = std::shared_ptr<const T>;

/*! \brief Shortcut function for making a shared pointer.
 *
 *  Currently use std::make_shared.
 */
template <typename T, typename... Args>
s_ptr<T> make_s(Args&&... args)
{
  return std::make_shared<T>(std::forward<Args>(args)...);
}

/*! @} */

} // namespace rummikub

#endif // RUMMIKUB_CORE__STDMEMORY_H

