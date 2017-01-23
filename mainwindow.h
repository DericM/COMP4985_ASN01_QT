#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_g1_resolve_clicked();

    void on_g2_resolve_clicked();

    void on_g3_resolve_clicked();

    void on_g4_resolve_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
