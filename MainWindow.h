#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "World.h"
#include "LifeCycle.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    World world;
    LifeCycle * lifeCycle;

    void updateGravityEstimation();

private slots:
    void on_spinRot_valueChanged(double v);
    void on_spinWheelRad_valueChanged(double v);
    void on_rdFloor_toggled(bool isOn);
    void on_btJump_clicked();
    void on_btClear_clicked();
    void on_rdTraceFloor_toggled(bool isOn);

    void on_chkTrOff_toggled(bool isOn);
    void on_chkTr1_toggled(bool isOn);
    void on_chkTr2_toggled(bool isOn);
};

#endif // MAINWINDOW_H
