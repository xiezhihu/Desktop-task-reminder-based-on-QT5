//
// Created by hu on 2025/5/27.
//

#ifndef UNTITLED_TASKDIALOG_H
#define UNTITLED_TASKDIALOG_H

#include <QDialog>



QT_BEGIN_NAMESPACE
namespace Ui { class TaskDialog; }
QT_END_NAMESPACE

class TaskDialog : public QDialog {
Q_OBJECT

public:
    explicit TaskDialog(QWidget *parent = nullptr);
    void setbiaoge();
    void Show();
    void tianchong();

    ~TaskDialog() override;
signals:
    void taskConfirmed(const QString &renwuming, const QString &renwumiaoshu, const QString &time);
private slots:
    void on_biaoge_cellClicked(int row,int column);
    void on_queren_clicked();
    void on_shanchurenwu_clicked();

private:
    Ui::TaskDialog *ui;
    int rowMax;
    int idx;//焦点
    bool doCellClicked;
    QString renwumiaoshu;
    QString time;
    QString renwuming;
};


#endif //UNTITLED_TASKDIALOG_H
