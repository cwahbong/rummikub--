#ifndef RUMMIKUB_CORE__UTIL_H
#define RUMMIKUB_CORE__UTIL_H

#define MUST_SPECIALIZE(cls_or_func) static_assert( \
    sizeof(cls_or_func*)<0, "template instance of \"" \
    #cls_or_func "\" must be specialized."\
    )

#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

namespace rummikub {
namespace core {

template <typename T> using  w_ptr = std::weak_ptr<T>;
template <typename T> using cw_ptr = std::weak_ptr<const T>;
template <typename T> using  s_ptr = std::shared_ptr<T>;
template <typename T> using cs_ptr = std::shared_ptr<const T>;

template <typename T>
class MessageTraits {
  // using Type = ...;
  // using MessageType = ...;
  MUST_SPECIALIZE(MessageTraits);
};

template <typename T, typename MTraits = MessageTraits<T>>
class Observable {
  using Callback = std::function<void(
      const cs_ptr<Observable<T, MTraits>>&,
      const typename MTraits::MessageType&
      )>;

private:
  std::vector<Callback> m_callbacks{};
  bool m_changed{};

protected:
  void addCallback(const Callback& callback) {
    m_callbacks.push_back(callback);
  }

  void removeCallback(const Callback& callback) {
    const auto& removeIt = std::find(m_callbacks.begin(),
        m_callbacks.end(), callback);
    std::swap(m_callbacks.end() - 1, removeIt);
    m_callbacks.pop_back();
  }

  void removeAllCallbacks() {
    m_callbacks.clear();
  }

  void setChanged(bool changed) {
    m_changed = changed;
  }

  bool isChanged() const {
    return m_changed;
  }

  void notify(const typename MTraits::MessageType& cs_message) const {
    if (m_changed) {
      for (auto& callback : m_callbacks) {
        callback(cs_ptr<Observable<T, MTraits>>{this}, cs_message);
      }
    }
  }
};

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__UTIL_H

