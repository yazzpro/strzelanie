#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qtimer.h>
#include <QtMultimedia/QtMultimedia>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::timerUpdate) );

}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::timerUpdate() {
    if (--counter == 0) nextStep();
}
void MainWindow::delay(int numSeconds) {
    counter = numSeconds;
}
void MainWindow::ding() {
    static auto player = new QMediaPlayer(this);
    static auto audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    // ...
    player->setSource(QUrl::fromLocalFile("ding.mp3"));
    audioOutput->setVolume(50);
    player->play();
}
void MainWindow::endSerie() {
    serie();
}
void MainWindow::nextStep() {
    ding();
    switch (currentState) {
        case state::aiming: rest(); break;
        case state::shooting: aim(); break;
        case state::resting: endSerie(); break; // dekrementuj licznik
        case state::preparing: trigger(); break;
        case state::nothing: prepare();
        }
}
void MainWindow::serie() {
    auto serie = ui->numSerie->value();
    if (serie > 0) {
        timer->start();
        prepare();
    } else {
        timer->stop();
        ui->status->setText("Koniec");
    }
      ui->numSerie->setValue(--serie);
}
void MainWindow::prepare() {
    currentState = state::preparing;
    ui->status->setText("Przygotuj się");
    setStyleSheet("background-color: yellow");
    delay(ui->numPrepare->value());
}

void MainWindow::aim() {
    currentState = state::aiming;
    ui->status->setText("Celuj dalej");
    setStyleSheet("background-color: blue");
    delay(ui->numAim->value() - ui->numShoot->value());
}
void MainWindow::trigger() {
    currentState = state::shooting;
    ui->status->setText("Praca na spuście");
    setStyleSheet("background-color: green");
    delay(ui->numShoot->value());
}
void MainWindow::rest() {
    currentState = state::resting;
    ui->status->setText("Odpoczynek");
    setStyleSheet("background-color: red");
    delay(ui->numRest->value());
}
void MainWindow::on_pushButton_clicked()
{
    serie();
}

