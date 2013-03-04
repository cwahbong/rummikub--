#ifndef RUMMIKUB_CORE__UTIL_H
#define RUMMIKUB_CORE__UTIL_H

#define MUST_SPECIALIZE(cls_or_func) static_assert( \
    sizeof(cls_or_func*)<0, "template instance of \"" \
    #cls_or_func "\" must be specialized."\

#include <functional>
#include <memory>
#include <set>

namespace rummikub {
namespace core {

template <typename T> using  w_ptr = std::weak_ptr<T>;
template <typename T> using cw_ptr = std::weak_ptr<const T>;
template <typename T> using  s_ptr = std::shared_ptr<T>;
template <typename T> using cs_ptr = std::shared_ptr<const T>;

template <typename MessageT>
class Observable;

template <typename MessageT>
using Observer = std::function<void(const cs_ptr<Observable<MessageT>>&, const cs_ptr<MessageT>&)>;

template <typename MessageT>
class Observable {
private:
  std::set<s_ptr<Observer<MessageT>>> m_observers{};
  bool m_changed{};

protected:
  void addObserver(const s_ptr<Observer<MessageT>>& s_observer) {
    m_observers.insert(s_observer);
  }

  void removeObserver(const s_ptr<Observer<MessageT>>& s_observer) {
    m_observers.remove(s_observer);
  }

  void removeAllObservers() {
    m_observers.clear();
  }

  void setChanged(bool changed) {
    m_changed = changed;
  }

  bool isChanged() const {
    return m_changed;
  }

  void notify(const cs_ptr<MessageT>& cs_message) const {
    if (m_changed) {
      for (const auto& observer : m_observers) {
        observer(this, cs_message);
      }
    }
  }
};

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__UTIL_H

