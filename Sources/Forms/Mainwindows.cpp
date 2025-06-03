#include "Mainwindows.h"
#include "ui_MainWindows.h"
#include <QFile>
#include <QMessageBox>



MainWindows::MainWindows(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindows){//如何让MainWindows对象树接上Taskdialog
    ui->setupUi(this);
    tdg=new TaskDialog(this);//内存交给对象树处理
    ad=new add(this);
    timer=new QTimer(this);
    player=new QMediaPlayer(this);
    //设置提示音
    player->setMedia(QUrl::fromLocalFile("5.30.MP3"));
    empty=true;

    //设置文本只读
    ui->renwumiaoshu->setReadOnly(true);
    ui->renwuname->setReadOnly(true);
    connect(tdg,&TaskDialog::taskConfirmed,this,[this](const QString &renwuming, const QString &renwumiaoshu, const QString &time){
        on_quxiao_clicked();
        empty=false;
        ui->renwuname->setText(renwuming);
        ui->renwumiaoshu->setText(renwumiaoshu);
        QTime qTime=QTime::fromString(time,"HH:mm");
        ui->timeEdit->setTime(qTime);
    });
    connect(timer, &QTimer::timeout, this, &MainWindows::updateCountdown);
}

MainWindows::~MainWindows() {
    delete ui;
}

void MainWindows::on_xuanzherenwu_triggered() {
    tdg->Show();
}

void MainWindows::on_tianjiarenwu_triggered() {
    ad->Show();
}

void MainWindows::on_queding_clicked() {
    if(!empty){
        currentTime= ui->timeEdit->time();
        QMessageBox::information(this, "提示", "倒计时开始");
        timer->start(1000);// 启动定时器，每隔 1 秒触发一次 timeout 信号
    }else{
        QMessageBox::warning(this, "提示", "未选择任务！");
    }
}

void MainWindows::updateCountdown() {
    currentTime = currentTime.addSecs(-1);//减少一秒
    ui->timeEdit->setTime(currentTime);
    if(currentTime==QTime(0,0,0)){
        timer->stop();
        QMessageBox::information(this, "提示", "倒计时结束！");
        player->play();
    }
}

void MainWindows::on_quxiao_clicked() {
    empty=true;
    timer->stop();
    ui->renwumiaoshu->clear();
    ui->timeEdit->setTime(QTime(0,0,0));
    ui->renwuname->clear();
}
