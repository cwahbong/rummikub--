#include "GameWidget.h"
#include "ui_GameWidget.h"

#include "Rummikub.h"
#include "StdMemory.h"

#include "QRummikub.h"

#include <QThread>

namespace rummikub {
namespace game {

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget)
{
    ui->setupUi(this);
}

GameWidget::~GameWidget()
{
    delete ui;
}

void
GameWidget::startNewGame()
{
  QRummikub* p_qRummikub = new QRummikub();
  Rummikub* p_rummikub; // = new Rummikub(...); TODO
  p_qRummikub->setRummikub(u_ptr<Rummikub>(p_rummikub));
  connect(this, SIGNAL(ready),
          p_qRummikub, SLOT(startGame()));

  QThread* p_thread = new QThread();
  connect(p_thread, SIGNAL(finished()),
          p_qRummikub, SLOT(deleteLater()));
  p_qRummikub->moveToThread(p_thread);
  p_thread->start();

  emit ready();
}

} // namespace game
} // namespace rummikub

