#ifndef RUMMIKUB_GAME__GAMESETDIALOG_H
#define RUMMIKUB_GAME__GAMESETDIALOG_H

#include <QDialog>

namespace Ui {
class GameSetDialog;
} // namespace Ui


namespace rummikub {
namespace game {

class GameSetDialog : public QDialog
{
  Q_OBJECT
    
public:
  explicit GameSetDialog(QWidget *parent = 0);
  ~GameSetDialog();

  int getPlayerNum();
    
private:
  Ui::GameSetDialog *ui;
};

} // namespace game
} // namespace rummikub

#endif // RUMMIKUB_GAME__GAMESETDIALOG_H
