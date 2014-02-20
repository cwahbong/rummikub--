#ifndef RUMMIKUB_GAME__SETWIDGET_H
#define RUMMIKUB_GAME__SETWIDGET_H

#include "StdMemory.h"

#include "CoreFwd.h"

#include <QWidget>

namespace Ui {
class SetWidget;
} // namespace Ui

namespace rummikub {
namespace game {

class SetWidget : public QWidget
{
  Q_OBJECT

public:
  explicit SetWidget(QWidget *parent = 0);
  ~SetWidget();

  cs_ptr<Set> getSet();

private slots:
  // void insertTile(const Tile& tile);
  // void removeTile(const Tile& tile);

private:
  Ui::SetWidget *ui;
  cs_ptr<Set> sp_set;
};

} // namespace game
} // namespace rummikub

#endif // RUMMIKUB_GAME__SETWIDGET_H
