#ifndef RUMMIKUB_GAME__SETWIDGET_H
#define RUMMIKUB_GAME__SETWIDGET_H

#include "StdMemory.h"

#include "CoreFwd.h"

#include "TileWidget.h"

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

  void setSet(const cs_ptr<Set>&);
  cs_ptr<Set> getSet();

  void insertTile(const Tile& tile);
  void removeTile(const Tile& tile);

signals:
  void chosen();
  void tileChosen(TileWidget*);

protected:
  virtual void dragEnterEvent(QDragEnterEvent*) override;
  virtual void dragLeaveEvent(QDragLeaveEvent*) override;
  virtual void dropEvent(QDropEvent*) override;

private slots:
  void onTileChosen();

private:
  Ui::SetWidget *ui;
  cs_ptr<Set> _sp_set;
};

} // namespace game
} // namespace rummikub

#endif // RUMMIKUB_GAME__SETWIDGET_H
