#ifndef RUMMIKUB_GAME__SETWIDGET_H
#define RUMMIKUB_GAME__SETWIDGET_H

#include "StdMemory.h"
#include "model/Set.h"

#include <QWidget>

namespace Ui {
class SetWidget;
} // namespace Ui

namespace rummikub {
namespace game {

class SetWidget : public QWidget
{
  Q_OBJECT
  using Set = core::Set;
  using Tile = core::Tile;

public:
  explicit SetWidget(QWidget *parent = 0);
  ~SetWidget();
  void bindSet(const std::shared_ptr<Set>&);
  void unbindSet();

signals:
  void tileInserted(const Tile& tile);
  void tileRemoved(const Tile& tile);

private slots:
  void insertTile(const Tile& tile);
  void removeTile(const Tile& tile);

private:
  Ui::SetWidget *ui;
  s_ptr<core::Set> m_sp_set;
  s_ptr<core::Set::TileCallback> m_sp_insertTileCallback;
  s_ptr<core::Set::TileCallback> m_sp_removeTileCallback;
};

} // namespace game
} // namespace rummikub

#endif // RUMMIKUB_GAME__SETWIDGET_H
