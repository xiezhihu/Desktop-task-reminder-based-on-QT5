
#ifndef UNTITLED_ADD_H
#define UNTITLED_ADD_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class add; }
QT_END_NAMESPACE

class add : public QDialog {
Q_OBJECT

public:
    explicit add(QWidget *parent = nullptr);
    void Show();

    ~add() override;
private slots:
    void on_baocun_clicked();

private:
    Ui::add *ui;
};


#endif //UNTITLED_ADD_H
