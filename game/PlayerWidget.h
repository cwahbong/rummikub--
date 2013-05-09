#ifndef RUMMIKUB_GAME__PLAYERWIDGET_H
#define RUMMIKUB_GAME__PLAYERWIDGET_H

#include "StdMemory.h"

#include "qmodel/Player.h"
#include "qmodel/Tile.h"

#include <QWidget>

namespace Ui {
class PlayerWidget;
} // namespace Ui

namespace rummikub {
namespace game {

class PlayerWidget : public QWidget
{
  Q_OBJECT
  using Player = qmodel::Player;
  using Tile = qmodel::Tile;

public:
  explicit PlayerWidget(QWidget *parent = 0);
  ~PlayerWidget();

  void bindPlayer(const Player*);
  void unbindPlayer();

private slots:
  void insertTile(const Tile&);
  void removeTile(const Tile&);

private:
  Ui::PlayerWidget *ui;
  const Player* m_p_player;
};

} // namespace game
} // namespace rummikub

#endif // RUMMIKUB_GAME__PLAYERWIDGET_H

