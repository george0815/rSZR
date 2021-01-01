#include "gw.h"
#include "ui_gw.h"
#include <QDir>
#include <QPixmap>
#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <set>
#include <stdio.h>
#include <ctype.h>



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



    //image formats
    set<string> formats =             {"png",
                                       "jfif",
                                       "jpg",
                                       "jpeg",
                                       "jpe",
                                       "raw",
                                       "jif",
                                       "dds",
                                       "jfi",
                                       "gif",
                                       "webp",
                                       "bmp",
                                       "tif",
                                       "tga",
                                       "tiff",
                                       "arw",
                                       "cr2",
                                       "nrw,"
                                       "k25",
                                      "dib",
                                       "heif",
                                      "heic",
                                      "ind",
                                      "indd",
                                      "indt",
                                      "jp2",
                                      "j2k",
                                      "jpf",
                                      "jpx",
                                      "jpm",
                                      "mj2"};


    //open file dialog so user caan choose img folder
    QFileDialog dialog;

    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly);

    QString path = dialog.getExistingDirectory(this, "Open Image Folder");



    QDir dir(path);

    QDir().mkdir(".\\Resized\\");



    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);



    //for counting how many files are valid(images)
    int i = 0;



    //if the folder chosen is valid, proceed with the resizing, if not then throw error
    if(!path.isEmpty()&& !path.isNull()){




        //checks how many valid files there are in the folder
        foreach (QFileInfo fileInfo, dir.entryInfoList()) {

            string lower = fileInfo.suffix().toLocal8Bit().constData();

            std::transform(lower.begin(), lower.end(), lower.begin(), std::tolower);

            if(formats.find(lower) != formats.end()){
               i++;
            }

        }


    //if there are valid files, proceed, if not, then throw error
    if(i > 0){

    //for each image in folder, resize it

    foreach (QFileInfo fileInfo, dir.entryInfoList()) {

            i++;

            string lower = fileInfo.suffix().toLocal8Bit().constData();

            std::transform(lower.begin(), lower.end(), lower.begin(), std::tolower);



            if(formats.find(lower) != formats.end()){

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

     }


    else{
            QMessageBox::information(this, "Error", "No valid images in folder.");
        }

    }

    else{
        QMessageBox::information(this, "Error", "No folder chosen.");
    }




    //if amount of valid images insside ressized folder is greater then one, then throw confirmation message
    if(i > 0){
        QMessageBox::information(this, "Finished", "Resizing process done.");
    }





}




void GW::on_exit_clicked()
{
    QCoreApplication::quit();
}
