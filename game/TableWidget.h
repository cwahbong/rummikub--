#ifndef RUMMIKUB_GAME__TABLEWIDGET_H
#define RUMMIKUB_GAME__TABLEWIDGET_H

#include <QWidget>

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
    
private:
    Ui::TableWidget *ui;
};

} // namespace game
} // namespace rummikub

#endif // RUMMIKUB_GAME__TABLEWIDGET_H

