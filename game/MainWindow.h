#ifndef RUMMIKUB_GAME__MAINWINDOW_H
#define RUMMIKUB_GAME__MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
} // namespace Ui


namespace rummikub {
namespace game {

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_actionStartNew_triggered(bool);

private:
  Ui::MainWindow *ui;
};

} // namespace game
} // namespace rummikub
#endif // RUMMIKUB_GAME__MAINWINDOW_H

