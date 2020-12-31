#include "gw.h"
#include "ui_gw.h"
#include <QDir>
#include <QPixmap>
#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>



using namespace std;

GW::GW(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GW)
{


    ui->setupUi(this);



}

GW::~GW()
{
    delete ui;
}


void GW::on_cropResize_clicked()
{



    QFileDialog dialog;

    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly);



    QString path = dialog.getExistingDirectory(this, "Open Sekiro Folder");


    QString imgDir = path;
    QDir dir(imgDir);

    QDir().mkdir(".\\Resized\\");



    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);




    int i = 0;


    //for eeach image in folderr, resize it
    foreach (QFileInfo fileInfo, dir.entryInfoList()) {





        if(fileInfo.suffix() == "png" || fileInfo.suffix() == "jpg" || fileInfo.suffix() == "jpeg"){
            i++;

            QImage img(fileInfo.filePath());

            QPixmap pixmap;
            pixmap = pixmap.fromImage(img.scaled(ui->Width->value(), ui->Height->value(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

            QString final = ("./Resized/" + fileInfo.fileName());


            QFile file(final);
            file.open(QIODevice::WriteOnly);
            pixmap.save(&file, "jpeg",100);
            file.close();


        }



    }

    //checks if folder had images in it
    if(i > 0){
        QMessageBox::information(this, "Finished", "Resizing process done.");
    }
    else{
         QMessageBox::information(this, "Error", "No valid images in folder.");
    }




}




void GW::on_exit_clicked()
{
    QCoreApplication::quit();
}
