#ifndef RUMMIKUB_GAME__GAMEWIDGET_H
#define RUMMIKUB_GAME__GAMEWIDGET_H

#include "QDelegate.h"

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

  void putTile(); // TODO
  void moveTile(); // TODO
  void restore();

public slots:
  void responseAsked(QDelegate*);

private slots:
  void on_doneButton_clicked(bool);
  void on_restoreButton_clicked(bool);

private:
  Ui::GameWidget *ui;
  QDelegate* _p_qDelegate;
};

} // namespace game
} // namespace rummikub

#endif // RUMMIKUB_GAME__GAMEWIDGET_H

