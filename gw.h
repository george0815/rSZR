#ifndef GW_H
#define GW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class GW; }
QT_END_NAMESPACE

class GW : public QMainWindow
{
    Q_OBJECT

public:
    GW(QWidget *parent = nullptr);
    ~GW();

private slots:

    //resizes images
    void on_cropResize_clicked();



private:
    Ui::GW *ui;
};
#endif // GW_H
