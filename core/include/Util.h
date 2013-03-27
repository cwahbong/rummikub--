#ifndef RUMMIKUB_CORE__UTIL_H
#define RUMMIKUB_CORE__UTIL_H

#define MUST_SPECIALIZE(cls_or_func) static_assert( \
    sizeof(cls_or_func*)<0, "template instance of \"" \
    #cls_or_func "\" must be specialized."\
    )

#include <algorithm>
#include <functional>
#include <memory>
#include <type_traits>
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
class CallbackTraits {
  // using MessageType = typename MTraits::MessageType;
  // using CallbackFunction<MessageType> = ...;
  MUST_SPECIALIZE(CallbackTraits);
};

template <typename T,
    typename MTraits = MessageTraits<T>,
    typename CTraits = CallbackTraits<T, MTraits>>
class Notifier;

template <typename T, typename MTraits, typename CTraits>
class Notifier {
public:
  using MessageType = typename MTraits::MessageType;
  template <MessageType mType>
  using Callback = typename CTraits::template CallbackFunction<mType>::Type;
  template <MessageType mType>
  using CallbackKey = typename std::vector<Callback<mType>>::size_type;

private:

  template <MessageType mType>
  std::vector<Callback<mType>>&
  _callbacks() const {
    static std::vector<Callback<mType>> v;
    return v;
  }

public:
  // TODO add to callbackVectors in constructor and destructor

  template <MessageType mType>
  CallbackKey<mType> addCallback(const Callback<mType>& callback) {
    auto& vcallbacks = _callbacks<mType>();
    const auto& empty_it = find(vcallbacks.begin(), vcallbacks.end(), nullptr);
    if (empty_it == vcallbacks.end()) {
      vcallbacks.push_back(callback);
      return vcallbacks.size() - 1;
    } else {
      const auto key = empty_it - vcallbacks.begin();
      *empty_it = callback;
      return key;
    }
  }

  template <MessageType mType>
  void removeCallback(CallbackKey<mType> key) {
    _callbacks<mType>()[key] = nullptr;
  }

  template <MessageType mType>
  void removeAllCallbacks() {
    _callbacks<mType>().clear();
  }

  template <MessageType mType, typename... CallbackArgs>
  void notify(CallbackArgs... args) const { // TODO add const to this function
    for (auto& callback : _callbacks<mType>()) {
      callback(args...);
    }
  }
};

} // namespace core
} // namespace rummikub

#endif // RUMMIKUB_CORE__UTIL_H

