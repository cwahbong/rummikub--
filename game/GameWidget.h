#ifndef RUMMIKUB_GAME__GAMEWIDGET_H
#define RUMMIKUB_GAME__GAMEWIDGET_H

#include "QDelegate.h"
#include "TileWidget.h"
#include "SetWidget.h"

#include <QWidget>

namespace Ui {
class GameWidget;
} // namespace Ui

namespace rummikub {
namespace game {

class GameWidget : public QWidget
{
  Q_OBJECT
    
public:
  explicit GameWidget(QWidget *parent = 0);
  ~GameWidget();

  void startNewGame();

signals:
  void readyForNewGame();

public slots:
  void chooseTile(TileWidget*, SetWidget*);
  void chooseSet(SetWidget*);

private slots:
  void responseAsked(QDelegate*);

  void someonePutTile(
      const cs_ptr<Player>&,
      const Tile&,
      const cs_ptr<Set>&);
  void someoneMoveTile(
      const cs_ptr<Player>&,
      const Tile&,
      const cs_ptr<Set>&,
      const cs_ptr<Set>&);
  void someoneRestore(
      const cs_ptr<Player>&,
      const cs_ptr<Table>&);

  void onGameStarted();
  void onGameEnded();
  void onTurnStarted(const cs_ptr<Player>&);
  void onTurnEnded(const cs_ptr<Player>&);

  void on_doneButton_clicked(bool);
  void on_restoreButton_clicked(bool);

private:
  Ui::GameWidget *ui;
  QDelegate* _p_qDelegate;
  TileWidget* _selectedTile;
  SetWidget* _selectedSetFrom;
};

} // namespace game
} // namespace rummikub

#endif // RUMMIKUB_GAME__GAMEWIDGET_H

