#ifndef RUMMIKUB_GAME__PLAYERWIDGET_H
#define RUMMIKUB_GAME__PLAYERWIDGET_H

#include "model/Hand.h"
#include "StdMemory.h"

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
  void tileChoosed(TileWidget*);

public slots:
  void insertTile(const Tile&);
  void removeTile(const Tile&);

  void tileToggled(bool);

private:
  Ui::PlayerWidget *ui;
};

} // namespace game
} // namespace rummikub

#endif // RUMMIKUB_GAME__PLAYERWIDGET_H

