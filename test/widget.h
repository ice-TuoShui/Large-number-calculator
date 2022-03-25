#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_addButton_clicked();

    void on_subButton_clicked();

    void on_mulButton_clicked();

    void on_modButton_clicked();

    void on_divButton_clicked();

    void on_Button_clicked();

    void on_Button_2_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
