#include "TileWidget.h"
#include "ui_TileWidget.h"

#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>

#include <QMessageBox>

namespace rummikub {
namespace game {

using Color = Tile::Color;

QString
TileWidget::getColorStyleSheet(const Color& c)
{
  switch (c) {
  case Color::INVALID:
    return "color: grey;";
  case Color::RED:
    return "color: red;";
  case Color::BLUE:
    return "color: blue;";
  case Color::YELLOW:
    return "color: darkorange;";
  case Color::BLACK:
    return "color: black;";
  default:
    return "color: green";
  }
}

TileWidget::TileWidget(QWidget *parent)
  : QWidget(parent),
    ui(new Ui::TileWidget)
{
  ui->setupUi(this);
}

TileWidget::~TileWidget()
{
  delete ui;
}

void
TileWidget::paintEvent(QPaintEvent* event)
{
  QWidget::paintEvent(event);
  int lineWidth = 2;
  int padding = lineWidth / 2;
  QPen pen;
  pen.setWidth(lineWidth);
  QPainter painter(this);
  painter.setPen(pen);
  painter.drawRoundedRect(padding, padding, width() - lineWidth, height() - lineWidth, 8.0, 6.0);
}

void
TileWidget::mousePressEvent(QMouseEvent* event)
{
  if (event->button() == Qt::LeftButton) {
    pressStartPoint = event->pos();
  }
}

void
TileWidget::mouseMoveEvent(QMouseEvent* event)
{
  if (event->buttons() & Qt::LeftButton) {
    if ((event->pos() - pressStartPoint).manhattanLength() >=
        QApplication::startDragDistance()) {
      event->accept();
      QDrag* drag = new QDrag(this);
      drag->setMimeData(new QMimeData);
      drag->setPixmap(grab());
      drag->setHotSpot(QPoint(16, 36));

      setVisible(false);
      emit chosen();
      drag->exec();
      setVisible(true);
    }
  }
}

void
TileWidget::setTile(const Tile& tile)
{
  ui->m_content->setStyleSheet(getColorStyleSheet(tile.getColor()));
  ui->m_content->setText(Tile::to_string(tile.getValue()).c_str());
  m_tile = tile;
}

Tile
TileWidget::getTile() const
{
  return m_tile;
}

} // namespace game
} // namespace rummikub

