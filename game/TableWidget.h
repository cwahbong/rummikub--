#ifndef RUMMIKUB_GAME__TABLEWIDGET_H
#define RUMMIKUB_GAME__TABLEWIDGET_H

#include "CoreFwd.h"
#include "StdMemory.h"
#include "model/Table.h"

#include "TileWidget.h"
#include "SetWidget.h"

#include <QWidget>

#include <map>

namespace Ui {
class TableWidget;
} // namespace Ui

namespace rummikub {
namespace game {

class TableWidget : public QWidget
{
  Q_OBJECT
    
public:
  explicit TableWidget(QWidget *parent = 0);
  ~TableWidget();

  void putTile(const Tile&, const cs_ptr<Set>&);
  void moveTile(const Tile&, const cs_ptr<Set>&, const cs_ptr<Set>&);
  void restore(const cs_ptr<Table>&);

  void insertSet(const cs_ptr<Set>&);

protected:
  virtual void dragEnterEvent(QDragEnterEvent*) override;
  virtual void dragLeaveEvent(QDragLeaveEvent*) override;
  virtual void dropEvent(QDropEvent*) override;

signals:
  void tileChosen(TileWidget*, SetWidget*);
  void setChosen(SetWidget*);

private:
  Ui::TableWidget *ui;
  std::map<cs_ptr<Set>, SetWidget*> _setMap;
};

} // namespace game
} // namespace rummikub

#endif // RUMMIKUB_GAME__TABLEWIDGET_H

