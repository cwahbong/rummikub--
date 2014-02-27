#include "GameWidget.h"
#include "ui_GameWidget.h"

#include "Player.h"
#include "Rummikub.h"
#include "StdMemory.h"

#include "QRummikub.h"

#include <QMessageBox>
#include <QThread>

namespace rummikub {
namespace game {

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget)
{
    ui->setupUi(this);
    connect(ui->playerWidget, &PlayerWidget::tileChosen,
            this, &GameWidget::chooseTile);
    connect(ui->tableWidget, &TableWidget::setChosen,
            this, &GameWidget::chooseSet);
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
  connect(this,        &GameWidget::readyForNewGame,
          p_qRummikub, &QRummikub::rummiStartGame);
  connect(p_qRummikub, &QRummikub::readyForResponse,
          this,        &GameWidget::responseAsked);

  connect(p_qRummikub, &QRummikub::rummiTilePut,
          this,        &GameWidget::someonePutTile);
  connect(p_qRummikub, &QRummikub::rummiTileMoved,
          this,        &GameWidget::someoneMoveTile);
  connect(p_qRummikub, &QRummikub::rummiRestored,
          this,        &GameWidget::someoneRestore);
  connect(p_qRummikub, &QRummikub::rummiGameStarted,
          this,        &GameWidget::onGameStarted);
  connect(p_qRummikub, &QRummikub::rummiGameEnded,
          this,        &GameWidget::onGameEnded);
  connect(p_qRummikub, &QRummikub::rummiTurnStarted,
          this,        &GameWidget::onTurnStarted);
  connect(p_qRummikub, &QRummikub::rummiTurnEnded,
          this,        &GameWidget::onTurnEnded);

  QThread* p_thread = new QThread();
  connect(p_thread, &QThread::finished,
          p_thread, &QThread::deleteLater);
  connect(p_thread,    &QThread::finished,
          p_qRummikub, &QRummikub::deleteLater);
  p_qRummikub->moveToThread(p_thread);
  p_thread->start();

  emit readyForNewGame();
}

void
GameWidget::chooseTile(TileWidget* p_tileWidget, SetWidget* p_setWidget)
{
  auto* p_senderWidget = sender();
  if (p_senderWidget == ui->playerWidget) {
    // ui->tableWidget->uncheckTiles();
  }
  else if (p_senderWidget == ui->tableWidget) {
    // ui->playerWidget->uncheckTiles();
  }
  _selectedTile = p_tileWidget;
  _selectedSetFrom = p_setWidget;
}

void
GameWidget::chooseSet(SetWidget* p_setWidget)
{
  const auto sp_toSet = (p_setWidget ? p_setWidget->getSet() : s_ptr<Set>());
  if (_selectedSetFrom) { // from other set
    _p_qDelegate->moveTile(_selectedTile->getTile(), _selectedSetFrom->getSet(), sp_toSet);
  }
  else { // from hand
    _p_qDelegate->putTile(_selectedTile->getTile(), sp_toSet);
  }
  _selectedTile = nullptr;
  _selectedSetFrom = nullptr;
}

void
GameWidget::responseAsked(QDelegate* p_qDelegate)
{
  ui->restoreButton->setEnabled(true);
  ui->doneButton->setEnabled(true);
  _p_qDelegate = p_qDelegate;
  p_qDelegate->startResponse();
}

void
GameWidget::someonePutTile(
    const cs_ptr<Player>& sp_player,
    const Tile& tile,
    const cs_ptr<Set>& sp_set)
{
  ui->tableWidget->putTile(tile, sp_set);
}

void
GameWidget::someoneMoveTile(
    const cs_ptr<Player>& sp_player,
    const Tile& tile,
    const cs_ptr<Set>& sp_set_from,
    const cs_ptr<Set>& sp_set_to)
{
  if (false) { // ui not handle this player
    // TODO UI perform move tile animation
    // table.moveTile(sp_set_from, sp_set_to, tile);
  }
}

void
GameWidget::someoneRestore(
    const cs_ptr<Player>& sp_player,
    const cs_ptr<Table>& sp_table)
{
  if (false) {
    // TODO UI perform restore animation
    // table.to(sp_table);
  }
}

void
GameWidget::onGameStarted()
{
  // TODO
}

void
GameWidget::onGameEnded()
{
  // TODO announce the winner and the score
}

void
GameWidget::onTurnStarted(
    const cs_ptr<Player>& sp_player)
{
  QMessageBox::information(this, "turn started", "hi");
  if (true) { // UI handle this player
    ui->playerWidget->setTiles(sp_player->getHand());
  } else {
    // Showing that it is OOO's turn
  }
}

void
GameWidget::onTurnEnded(
    const cs_ptr<Player>&)
{
  if (true) { // UI handle this player
    // finalize the playerWidget
    // playerWidget.setPlayer(nullptr);
  } else {
    // Showing that a player ends its turn
  }
}

void
GameWidget::on_doneButton_clicked(bool)
{
  ui->restoreButton->setEnabled(false);
  ui->doneButton->setEnabled(false);
  _p_qDelegate->endResponse();
  _p_qDelegate = nullptr;
}

void
GameWidget::on_restoreButton_clicked(bool)
{
  _p_qDelegate->restore();
}

} // namespace game
} // namespace rummikub
