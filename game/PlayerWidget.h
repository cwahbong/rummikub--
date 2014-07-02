#ifndef RUMMIKUB_GAME__PLAYERWIDGET_H
#define RUMMIKUB_GAME__PLAYERWIDGET_H

#include "model/Hand.h"
#include "StdMemory.h"

#include "SetWidget.h"
#include "TileWidget.h"

#include <QWidget>

namespace Ui {
class PlayerWidget;
} // namespace Ui

namespace rummikub {
namespace game {

class PlayerWidget : public QWidget
{
  Q_OBJECT

public:
  explicit PlayerWidget(QWidget *parent = 0);
  ~PlayerWidget();

  void setTiles(const cs_ptr<Hand>&);

signals:
  void tileChosen(TileWidget*, SetWidget*);

public slots:
  void insertTile(const Tile&);
  void removeTile(const Tile&);

private slots:
  void onTileChosen();

private:
  Ui::PlayerWidget *ui;
};

} // namespace game
} // namespace rummikub

#endif // RUMMIKUB_GAME__PLAYERWIDGET_H

