#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia/QtMultimedia>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    QTimer *timer;
    int counter;
    Ui::MainWindow *ui;
    void prepare();
    void aim();
    void trigger();
    void rest();
    void delay(int numSeconds);
    void ding();
    void timerUpdate();
    void serie();
    void nextStep();
    void endSerie();
    enum state { nothing, preparing, shooting, aiming, resting } currentState;

    QMediaPlayer *player;
    QAudioOutput *audioOutput;

};
#endif // MAINWINDOW_H
