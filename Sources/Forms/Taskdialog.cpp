#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include "Taskdialog.h"
#include "ui_TaskDialog.h"


TaskDialog::TaskDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::TaskDialog) {
    ui->setupUi(this);
    ui->biaoge->setEditTriggers(QAbstractItemView::NoEditTriggers);
    idx=-1;

    setbiaoge();
//    connect(ui->shanchurenwu,&QPushButton::clicked,this,TaskDialog::on_shanchurenwu_clicked);

}

TaskDialog::~TaskDialog() {
    delete ui;
}

void TaskDialog::setbiaoge() {
    ui->biaoge->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->biaoge->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}//填充窗口

void TaskDialog::Show() {
    ui->biaoge->clearContents();//保留标题，其它单元格清空
    tianchong();
    doCellClicked=false;
    this->show();
}

void TaskDialog::tianchong() {
    ui->biaoge->clear();
    idx=-1;
    doCellClicked=false;
    QFile file("output.json");
    file.open(QIODevice::ReadOnly);
    auto all=file.readAll();//读取内容
    auto doc=QJsonDocument::fromJson(all);
    auto obj=doc.array();
    rowMax=obj.size();
    int i=0;
    for(auto it:obj){
        QJsonObject jsonObject=it.toObject();
        QString renwuming=jsonObject["任务名"].toString();
        auto rwm=new QTableWidgetItem(renwuming);
        ui->biaoge->setItem(i,0,rwm);

        QString renwumiaoshu=jsonObject["任务描述"].toString();
        auto rwms=new QTableWidgetItem(renwumiaoshu);
        ui->biaoge->setItem(i,1,rwms);

        QString time=jsonObject["时间"].toString();
        auto t=new QTableWidgetItem(time);
        ui->biaoge->setItem(i,2,t);
        i++;
    }

    file.close();

}

void TaskDialog::on_biaoge_cellClicked(int row, int column) {
    if(row>=rowMax){
        return ;
    }
    //获取选中的任务信息
    idx=row;//当前焦点行数
    QString text1=ui->biaoge->item(row,0)->text();
    QString text2=ui->biaoge->item(row,1)->text();
    QString text3=ui->biaoge->item(row,2)->text();
    renwuming=text1;
    renwumiaoshu=text2;
    time=text3;
    doCellClicked=true;
}

void TaskDialog::on_queren_clicked() {
    if(doCellClicked && idx>=0){
        emit taskConfirmed(renwuming,renwumiaoshu,time);
        this->close();

    }else{
        QMessageBox::warning(this, "错误", "未选择任务");
    }
}

void TaskDialog::on_shanchurenwu_clicked() {
    if(doCellClicked){
        QJsonArray arr;
        QFile file("output.json");
        if(file.open(QIODevice::ReadOnly)){//读取原Json文件删除对应任务
            auto all=file.readAll();
            arr=QJsonDocument::fromJson(all).array();
            arr.erase(arr.begin()+idx);
            file.close();
            QMessageBox::information(this,"successful","删除成功");
        }else{
            QMessageBox::warning(this,"错误","文件无法打开");
            return ;
        }
        //将新内容写回
        QFile write("output.json");
        file.open(QIODevice::WriteOnly);
        QJsonDocument doc(arr);
        file.write(doc.toJson(QJsonDocument::Indented));// doc 中的 JSON 内容写入文件,序列化
        file.close();


        //重新填充数据
        tianchong();


    }else{
        QMessageBox::warning(this,"错误","未选择任务");
    }

}






