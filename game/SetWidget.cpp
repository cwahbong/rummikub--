#include "SetWidget.h"
#include "ui_SetWidget.h"

#include "TileWidget.h"

#include "qmodel/Set.h"

#include "model/Tile.h"

#include <QLayout>

using std::make_shared;

namespace rummikub {
namespace game {

SetWidget::SetWidget(QWidget *parent)
  : QWidget(parent),
    ui(new Ui::SetWidget)
{
  ui->setupUi(this);
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
  // TODO lock the sp_set
  m_sp_set = sp_set;
  for (const auto& tile : sp_set->getValidatedTiles()) {
    insertTile(tile);
  }
  QObject::connect(
    sp_set.get(), SIGNAL(tileInserted(const Tile&)),
    this, SLOT(insertTile(const Tile&))
  );
  QObject::connect(
    sp_set.get(), SIGNAL(tileRemoved(const Tile&)),
    this, SLOT(removeTile(const Tile&))
  );
  // TODO unlock the sp_set
}

void
SetWidget::unbindSet()
{
  if (m_sp_set) {
    QObject::disconnect(
      m_sp_set.get(), SIGNAL(tileInserted(const Tile&)),
      this, SLOT(insertTile(const Tile&))
    );
    QObject::disconnect(
      m_sp_set.get(), SIGNAL(tileRemoved(const Tile&)),
      this, SLOT(removeTile(const Tile&))
    );
    m_sp_set = nullptr;
  }
  for (auto* p_tileWidget : findChildren<TileWidget*>()) {
    p_tileWidget->deleteLater();
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
