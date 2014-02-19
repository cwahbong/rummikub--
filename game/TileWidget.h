#ifndef RUMMIKUB_GAME__TILEWIDGET_H
#define RUMMIKUB_GAME__TILEWIDGET_H

#include <QAbstractButton>

#include "CoreFwd.h"
#include "model/Tile.h"

namespace Ui {
class TileWidget;
} // namespace Ui

namespace rummikub {
namespace game {

class TileWidget : public QAbstractButton
{
  Q_OBJECT
  static QString getColorStyleSheet(const Tile::Color&);

public:
  explicit TileWidget(QWidget *parent = 0);
  ~TileWidget();

  void setTile(const Tile& tile);
  Tile getTile() const;

protected:
  virtual void paintEvent(QPaintEvent* event);

private:
  Ui::TileWidget *ui;
  Tile m_tile{Tile::Color::INVALID, 14};
};

} // namespace game
} // namespace rummikub

#endif // RUMMIKUB_GAME__TILEWIDGET_H

