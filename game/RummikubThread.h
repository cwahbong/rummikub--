#ifndef RUMMIKUB_GAME__RUMMIKUBTHREAD_H
#define RUMMIKUB_GAME__RUMMIKUBTHREAD_H

#include "CoreFwd.h"
#include "StdMemory.h"

#include <QThread>

namespace rummikub {

class RummikubThread : public QThread
{
  Q_OBJECT

public:
  explicit RummikubThread(
      u_ptr<Rummikub>&& up_rummikub,
      QObject *parent = 0);
  virtual ~RummikubThread();

protected:
  void run();

private:
  u_ptr<Rummikub> _up_rummikub;
};

} // namespace rummikub

#endif // RUMMIKUB_GAME__RUMMIKUBTHREAD_H
