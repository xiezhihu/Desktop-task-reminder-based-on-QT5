#include <QJsonDocument>
#include <QFile>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include "add.h"
#include "ui_add.h"


add::add(QWidget *parent) :
        QDialog(parent), ui(new Ui::add) {
    ui->setupUi(this);
}

add::~add() {
    delete ui;
}

void add::Show() {
    ui->xinjianrenwuming->clear();
    ui->time->setTime(QTime(0,0));//设置时间归零
    ui->renwumiaoshu->clear();
    this->show();
}

void add::on_baocun_clicked() {
    QString url="output.json";
    bool exists = QFile::exists(url);
    if (!exists) {
        QMessageBox::warning(this,"错误","文件不存在，已创建");
        qDebug() << "文件不存在:";
        QFile write(url);
        write.open(QIODevice::WriteOnly);
        write.close();
    }



    //读取原始内容
    QFile read(url);
    if(!read.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this, "错误", "无法打开文件");
        return;
    }
    auto all=read.readAll();
    auto doc=QJsonDocument::fromJson(all).array();//以json文本读出转化为数组
    read.close();




    //开始追加
    QJsonObject obj;//创建一个json对象

    //获取任务名
    auto textname=ui->xinjianrenwuming->text();
    obj["任务名"]=textname;


    //获取时间
    auto time=ui->time->time();
    QString timeString = time.toString("HH:mm");
    obj["时间"]=timeString;


    //获取任务描述
    auto text=ui->renwumiaoshu->toPlainText();
    obj["任务描述"]=text;


    QFile file(url);//创建一个 QFile 对象，表示文件名为 output.json
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "文件打开/创建失败，错误码:" << file.error();
        qDebug() << "错误详情:" << file.errorString();
        QMessageBox::warning(this, "错误", "无法打开文件: " + file.errorString());
        return;
    }else{
        doc.push_front(obj);
        QJsonDocument tar(doc);

        file.write(tar.toJson(QJsonDocument::Indented));// doc 中的 JSON 内容写入文件,序列化
        file.close();
    }

    QMessageBox::information(this, "succeed", "保存成功");
    this->close();
}
