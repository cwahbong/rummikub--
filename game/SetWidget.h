#ifndef RUMMIKUB_GAME__SETWIDGET_H
#define RUMMIKUB_GAME__SETWIDGET_H

#include "Set.h"
#include "StdMemory.h"

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
  void bindSet(const std::shared_ptr<core::Set>&);
  void unbindSet();

signals:

public slots:

private:
  Ui::SetWidget *ui;
  s_ptr<core::Set> m_sp_set;
  s_ptr<core::Set::TileCallback> m_sp_insertTileCallback;
  s_ptr<core::Set::TileCallback> m_sp_removeTileCallback;
};

} // namespace game
} // namespace rummikub

#endif // RUMMIKUB_GAME__SETWIDGET_H
