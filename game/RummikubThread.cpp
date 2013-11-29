#include "RummikubThread.h"

#include "Rummikub.h"

#include <utility>

namespace rummikub {

RummikubThread::RummikubThread(u_ptr<Rummikub>&& up_rummikub, QObject *parent)
  : QThread(parent),
    _up_rummikub(std::move(up_rummikub))
{
}

RummikubThread::~RummikubThread()
{/* Empty. */}

void
RummikubThread::run()
{
  _up_rummikub->startGame();
}

} // namespace rummikub
