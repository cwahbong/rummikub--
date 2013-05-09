#ifndef RUMMIKUB_GAME__SETWIDGET_H
#define RUMMIKUB_GAME__SETWIDGET_H

#include "StdMemory.h"

#include "CoreFwd.h"

#include "qmodel/Fwd.h"

#include <QWidget>

namespace Ui {
class SetWidget;
} // namespace Ui

namespace rummikub {
namespace game {

class SetWidget : public QWidget
{
  Q_OBJECT
  using Set = qmodel::Set;
  using Tile = core::Tile;

public:
  explicit SetWidget(QWidget *parent = 0);
  ~SetWidget();
  void bindSet(const s_ptr<Set>&);
  void unbindSet();

private slots:
  void insertTile(const Tile& tile);
  void removeTile(const Tile& tile);

private:
  Ui::SetWidget *ui;
  s_ptr<Set> m_sp_set;
};

} // namespace game
} // namespace rummikub

#endif // RUMMIKUB_GAME__SETWIDGET_H
