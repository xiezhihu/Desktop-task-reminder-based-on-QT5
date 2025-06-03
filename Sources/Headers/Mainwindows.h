

#ifndef UNTITLED_MAINWINDOWS_H
#define UNTITLED_MAINWINDOWS_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QMediaPlayer>
#include "Taskdialog.h"
#include "add.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindows; }
QT_END_NAMESPACE

class MainWindows : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindows(QWidget *parent = nullptr);

    ~MainWindows() override;
private slots:
    void on_xuanzherenwu_triggered();
    void on_tianjiarenwu_triggered();
    void on_queding_clicked();
    void on_quxiao_clicked();
    void updateCountdown(); // 每秒触发的函数


private:
    Ui::MainWindows *ui;
    TaskDialog *tdg;//任务管理窗口
    add *ad;//任务添加窗口
    QTime currentTime;//当前窗口时间
    QTimer *timer;
    bool empty;//判空
    QMediaPlayer *player;//MP3控制

};

#endif //UNTITLED_MAINWINDOWS_H
