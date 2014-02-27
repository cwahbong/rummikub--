#ifndef RUMMIKUB_GAME__TILEWIDGET_H
#define RUMMIKUB_GAME__TILEWIDGET_H

#include <QWidget>

#include "CoreFwd.h"
#include "model/Tile.h"

namespace Ui {
class TileWidget;
} // namespace Ui

namespace rummikub {
namespace game {

class TileWidget : public QWidget
{
  Q_OBJECT
  static QString getColorStyleSheet(const Tile::Color&);

public:
  explicit TileWidget(QWidget *parent = 0);
  ~TileWidget();

  void setTile(const Tile&);
  Tile getTile() const;

protected:
  virtual void paintEvent(QPaintEvent*) override;

  virtual void mousePressEvent(QMouseEvent*) override;
  virtual void mouseMoveEvent(QMouseEvent*) override;

signals:
  void chosen();
  void unchosen();

private:
  Ui::TileWidget *ui;
  Tile m_tile{Tile::Color::INVALID, 14};
  QPoint pressStartPoint;
};

} // namespace game
} // namespace rummikub

#endif // RUMMIKUB_GAME__TILEWIDGET_H

