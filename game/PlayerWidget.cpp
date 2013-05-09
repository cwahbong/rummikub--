#include "PlayerWidget.h"
#include "ui_PlayerWidget.h"

namespace rummikub {
namespace game {

PlayerWidget::PlayerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerWidget),
    m_p_player{nullptr}
{
    ui->setupUi(this);
}

PlayerWidget::~PlayerWidget()
{
    delete ui;
}

void
PlayerWidget::bindPlayer(const Player* p_player)
{
  m_p_player = p_player;
  QObject::connect(
    m_p_player, SIGNAL(tileInserted(const Tile&)),
    this, SLOT(insertTile(const Tile&))
  );
  QObject::connect(
    m_p_player, SIGNAL(tileRemoved(const Tile&)),
    this, SLOT(removeTile(const Tile&))
  );
  // TODO add tile widgets
}

void
PlayerWidget::unbindPlayer()
{
  if (m_p_player) {
    QObject::disconnect(
      m_p_player, SIGNAL(tileInserted(const Tile&)),
      this, SLOT(insertTile(const Tile&))
    );
    QObject::disconnect(
      m_p_player, SIGNAL(tileRemoved(const Tile&)),
      this, SLOT(removeTile(const Tile&))
    );
    // TODO remove all tile widgets
  }
}

void
PlayerWidget::insertTile(const Tile&)
{
  // TODO
}

void
PlayerWidget::removeTile(const Tile&)
{
  // TODO
}

} // namespace game
} // namespace rummikub

