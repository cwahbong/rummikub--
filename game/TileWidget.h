#ifndef RUMMIKUB_GAME__TILEWIDGET_H
#define RUMMIKUB_GAME__TILEWIDGET_H

#include <QWidget>

#include "CoreFwd.h"

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

protected:
  virtual void paintEvent(QPaintEvent* event);

private:
  Ui::TileWidget *ui;
};

} // namespace game
} // namespace rummikub

#endif // RUMMIKUB_GAME__TILEWIDGET_H

