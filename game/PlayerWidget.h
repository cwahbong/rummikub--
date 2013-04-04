#ifndef RUMMIKUB_GAME__PLAYERWIDGET_H
#define RUMMIKUB_GAME__PLAYERWIDGET_H

#include <QWidget>

namespace Ui {
class PlayerWidget;
} // namespace Ui

namespace rummikub {
namespace game {

class PlayerWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit PlayerWidget(QWidget *parent = 0);
    ~PlayerWidget();
    
private:
    Ui::PlayerWidget *ui;
};

} // namespace game
} // namespace rummikub

#endif // RUMMIKUB_GAME__PLAYERWIDGET_H

