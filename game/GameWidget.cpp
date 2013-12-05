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
  ui->restoreButton->setEnabled(false);
  ui->doneButton->setEnabled(false);

  QRummikub* p_qRummikub = new QRummikub({{"player 1", nullptr}});
  connect(this,        SIGNAL(readyForNewGame()),
          p_qRummikub, SLOT(rummiStartGame()));
  connect(p_qRummikub, SIGNAL(readyForResponse(QDelegate*)),
          this,        SLOT(responseAsked(QDelegate*)));

  QThread* p_thread = new QThread();
  connect(p_thread, SIGNAL(finished()),
          p_thread, SLOT(deleteLater()));
  connect(p_thread,    SIGNAL(finished()),
          p_qRummikub, SLOT(deleteLater()));
  p_qRummikub->moveToThread(p_thread);
  p_thread->start();

  emit readyForNewGame();
}

void
GameWidget::responseAsked(QDelegate* p_qDelegate)
{
  ui->restoreButton->setEnabled(true);
  ui->doneButton->setEnabled(true);
  _p_qDelegate = p_qDelegate;
  p_qDelegate->startResponse();
}

void GameWidget::on_doneButton_clicked(bool)
{
  ui->restoreButton->setEnabled(false);
  ui->doneButton->setEnabled(false);
  _p_qDelegate->endResponse();
  _p_qDelegate = NULL;
}

void GameWidget::on_restoreButton_clicked(bool)
{
  _p_qDelegate->restore();
}

} // namespace game
} // namespace rummikub
