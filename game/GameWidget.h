#ifndef RUMMIKUB_GAME__GAMEWIDGET_H
#define RUMMIKUB_GAME__GAMEWIDGET_H

#include <QWidget>

namespace Ui {
class GameWidget;
} // namespace Ui

namespace rummikub {
namespace game {

class GameWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit GameWidget(QWidget *parent = 0);
    ~GameWidget();
    
private:
    Ui::GameWidget *ui;
};

} // namespace game
} // namespace rummikub

#endif // RUMMIKUB_GAME__GAMEWIDGET_H

