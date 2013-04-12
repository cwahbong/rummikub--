#include "SetWidget.h"
#include "ui_SetWidget.h"

#include "TileWidget.h"

#include "Rummikub.h"
#include "Tile.h"

#include <QLayout>

using std::make_shared;

using rummikub::core::Set;
using rummikub::core::Tile;

namespace rummikub {
namespace game {

SetWidget::SetWidget(QWidget *parent)
  : QWidget(parent),
    ui(new Ui::SetWidget)
{
  ui->setupUi(this);
  QObject::connect(this, SIGNAL(tileInserted(const Tile&)),
                   this, SLOT(insertTile(const Tile&)));
  QObject::connect(this, SIGNAL(tileRemoved(const Tile&)),
                   this, SLOT(removeTile(const Tile&)));
}

SetWidget::~SetWidget()
{
  unbindSet();
  delete ui;
}

void
SetWidget::bindSet(const s_ptr<Set>& sp_set)
{
  unbindSet();
  for (const auto& tile : sp_set->getValidatedTiles()) {
    insertTile(tile);
  }
  m_sp_set = sp_set;
  m_sp_insertTileCallback = make_shared<Set::TileCallback>(
    [this](const Tile& tile) {
      emit tileInserted(tile);
    }
  );
  sp_set->addInsertTileCallback(m_sp_insertTileCallback);
  m_sp_removeTileCallback = make_shared<Set::TileCallback>(
    [this](const Tile& tile) {
      emit tileRemoved(tile);
    }
  );
  sp_set->addRemoveTileCallback(m_sp_removeTileCallback);
}

void
SetWidget::unbindSet()
{
  for (auto* p_tileWidget : findChildren<TileWidget*>()) {
    p_tileWidget->deleteLater();
  }
  if (m_sp_set) {
    m_sp_set->delInsertTileCallback(m_sp_insertTileCallback);
    m_sp_set->delInsertTileCallback(m_sp_removeTileCallback);
    m_sp_set = nullptr;
  }
}

void
SetWidget::insertTile(const Tile& tile)
{
  auto* p_tile = new TileWidget();
  p_tile->setTile(tile);
  layout()->addWidget(p_tile);
}

void
SetWidget::removeTile(const Tile& tile)
{
  for (auto* p_tileWidget : findChildren<TileWidget*>()) {
    if (p_tileWidget->getTile() == tile) {
      p_tileWidget->deleteLater();
      break;
    }
  }
}

} // namespace game
} // namespace rummikub
