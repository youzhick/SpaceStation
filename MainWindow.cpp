#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QtCore>
#include "YTools/Utils/YConstants.h"

using namespace Yt;
// *********************************************************************************************************************
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , lifeCycle (nullptr)
{
    ui->setupUi(this);

    world.setWheelSpeed(ui->spinRot->value()*2*PI/60.0);
    world.setWheelRadius(ui->spinWheelRad->value());
    ui->drawer->setStickToFloor(ui->rdFloor->isChecked());
    ui->drawer->setStickTraceToFloor(ui->rdTraceFloor->isChecked());

    updateGravityEstimation();


    ui->drawer->setWorld(&world);

    lifeCycle = new LifeCycle(this);
    lifeCycle->setWorld(&world);

    connect(lifeCycle, SIGNAL(signalWorldUpdated()), ui->drawer, SLOT (repaint()));

    lifeCycle->start();

} // MainWindow()
// *********************************************************************************************************************
MainWindow::~MainWindow()
{
    if (lifeCycle)
    {
        lifeCycle->stop();
        if (!lifeCycle->wait(2000))
            lifeCycle->terminate();
        delete  lifeCycle;
    } // if

    delete ui;
} // ~MainWindow()
// *********************************************************************************************************************
void MainWindow::on_spinRot_valueChanged(double v) {
    world.setWheelSpeed(v*2*PI/60.0);
    updateGravityEstimation();
} // on_spinRot_valueChanged()
// *********************************************************************************************************************
void MainWindow::on_spinWheelRad_valueChanged(double v) {
    world.setWheelRadius(v);
    updateGravityEstimation();
} // on_spinWheelRad_valueChanged()
// *********************************************************************************************************************
void MainWindow::on_rdFloor_toggled(bool isOn) {
    ui->drawer->setStickToFloor(isOn);
    ui->drawer->clearPath();
} // on_rdFloor_toggled()
// *********************************************************************************************************************
void MainWindow::on_rdTraceFloor_toggled(bool isOn) {
    ui->drawer->setStickTraceToFloor(isOn);
    ui->drawer->clearPath();
} // on_rdTraceFloor_toggled()
// *********************************************************************************************************************
void MainWindow::on_btJump_clicked() {
    double angle = 0;
    if (ui->rdLeft->isChecked())
        angle = -PI/4;
    else if (ui->rdRight->isChecked())
        angle = PI/4;

    double speed = ui->spinJump->value();

    ui->drawer->clearPath();
    world.doJump(speed, angle);

    qDebug() << "Jumping";
} // on_btJump_clicked()
// *********************************************************************************************************************
void MainWindow::on_btClear_clicked() {
    ui->drawer->clearPath();
} // on_btClear_clicked()
// *********************************************************************************************************************
void MainWindow::on_chkTrOff_toggled(bool isOn) {
    if (!isOn)
        return;
    ui->drawer->setDrawTrace(0);
    ui->drawer->clearPath();
} // on_chkTrOff_toggled()
// *********************************************************************************************************************
void MainWindow::on_chkTr1_toggled(bool isOn) {
    if (!isOn)
        return;
    ui->drawer->setDrawTrace(1);
    ui->drawer->clearPath();
}
// *********************************************************************************************************************
void MainWindow::on_chkTr2_toggled(bool isOn) {
    if (!isOn)
        return;
    ui->drawer->setDrawTrace(2);
    ui->drawer->clearPath();
} // on_chkTr2_toggled()
// *********************************************************************************************************************
void MainWindow::updateGravityEstimation() {
    double rpm = ui->spinRot->value();
    double r = ui->spinWheelRad->value();

    double a = rpm*2*PI/60.0;
    double g = a*a*r/9.81;

    ui->labelGravity->setText(QString("Virtual gravity estimation: %1 g").arg(g));
    ui->labelGravity->repaint();
} // updateGravityEstimation()
// *********************************************************************************************************************
