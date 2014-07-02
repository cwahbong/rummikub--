#include "GameWidget.h"
#include "ui_GameWidget.h"

#include "Player.h"
#include "Rummikub.h"
#include "StdMemory.h"

#include "QRummikub.h"

#include <QMessageBox>
#include <QThread>

#include <QDebug>

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
    connect(ui->tableWidget, &TableWidget::tileChosen,
            this, &GameWidget::chooseTile);
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
  if (p_tileWidget) {
    _selectedTile = p_tileWidget;
    _selectedSetFrom = p_setWidget;
  }
}

void
GameWidget::chooseSet(SetWidget* p_setWidget)
{
  const auto sp_toSet = (p_setWidget ? p_setWidget->getSet() : s_ptr<Set>());
  if (_selectedSetFrom) { // from other set
    if (_selectedSetFrom->getSet() != sp_toSet) {
      emit tileMoved(_selectedTile->getTile(), _selectedSetFrom->getSet(), sp_toSet);
      qDebug() << "Move" << _selectedTile->getTile().getValue();
    }
  }
  else { // from hand
    if (_selectedTile) {
      emit tilePut(_selectedTile->getTile(), sp_toSet);
      qDebug() << "Put" << _selectedTile->getTile().getValue() << sp_toSet.get();
    } else {
      qDebug() << "ChooseSet error: no tile selected.";
    }
  }
  _selectedTile = nullptr;
  _selectedSetFrom = nullptr;
}

void
GameWidget::responseAsked(QDelegate* p_qDelegate)
{
  ui->restoreButton->setEnabled(true);
  ui->doneButton->setEnabled(true);
  connect(this, &GameWidget::tilePut,
          p_qDelegate, &QDelegate::putTile);
  connect(this, &GameWidget::tileMoved,
          p_qDelegate, &QDelegate::moveTile);
  connect(this, &GameWidget::restored,
          p_qDelegate, &QDelegate::restore);
  connect(this, &GameWidget::endResponse,
          p_qDelegate, &QDelegate::endResponse);
  qDebug() << "GameWidget response asked.\n";
}

void
GameWidget::someonePutTile(
    const cs_ptr<Player>& sp_player,
    const Tile& tile,
    const cs_ptr<Set>& sp_set)
{
  qDebug() << "someone put tile.\n";
  ui->tableWidget->putTile(tile, sp_set);
  if (true) { // ui handled player
    ui->playerWidget->removeTile(tile);
  }
}

void
GameWidget::someoneMoveTile(
    const cs_ptr<Player>& sp_player,
    const Tile& tile,
    const cs_ptr<Set>& sp_set_from,
    const cs_ptr<Set>& sp_set_to)
{
  if (false) { // ui not handle this player
    ui->tableWidget->animateMoveTile(sp_set_from, sp_set_to, tile);
  } else {
    qDebug() << "GameWidget: someoneMoveTile";
    ui->tableWidget->moveTile(tile, sp_set_from, sp_set_to);
  }
}

void
GameWidget::someoneRestore(
    const cs_ptr<Player>& sp_player,
    const cs_ptr<Table>& sp_table)
{
  // ui->tableWidget->animateTo(sp_table);
  ui->tableWidget->restore(sp_table);
  ui->playerWidget->setTiles(sp_player->getHand());
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
  // ui->tableWidget->setTable(p_qDelegate->getTable());
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
  // ui->tableWidget->setTable(p_qDelegate->getTable());
  if (true) { // UI handle this player
    // playerWidget.setTiles(sp_player->getHand());
  } else {
    // Showing that a player ends its turn
  }
}

void
GameWidget::on_doneButton_clicked(bool)
{
  ui->restoreButton->setEnabled(false);
  ui->doneButton->setEnabled(false);
  emit endResponse();
}

void
GameWidget::on_restoreButton_clicked(bool)
{
  emit restored();
}

} // namespace game
} // namespace rummikub
