#ifndef RUMMIKUB_GAME__TILEWIDGET_H
#define RUMMIKUB_GAME__TILEWIDGET_H

#include <QWidget>

#include "CoreFwd.h"
#include "Tile.h"

namespace Ui {
class TileWidget;
} // namespace Ui

namespace rummikub {
namespace game {

class TileWidget : public QWidget
{
  Q_OBJECT
  static QString getColorStyleSheet(core::Color);

public:
  explicit TileWidget(QWidget *parent = 0);
  ~TileWidget();

  void setTile(const core::Tile& tile);
  core::Tile getTile() const;

protected:
  virtual void paintEvent(QPaintEvent* event);

private:
  Ui::TileWidget *ui;
  core::Tile m_tile{core::INVALID, 14};
};

} // namespace game
} // namespace rummikub

#endif // RUMMIKUB_GAME__TILEWIDGET_H

