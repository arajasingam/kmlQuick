#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include "kmldom.h"
#include "kmlreader.h"
#include "kmlwriter.h"

void usageWriter(){
    qDebug() << "\tkml Writer usage...";

}
void usageReader(){
    qDebug() << "\tkml Reader usage...";

    QString filename = "C:/Users/Akshayan/Documents/Git Repositories/kmlQuick/examples/Example pack.kml";
    QFile file(filename);
        if(!file.open(QFile::ReadOnly | QFile::Text)){
            qDebug()<<"Cannot Open File:" << file.errorString();
            return;
        }
        kmlElement::document* doc = new kmlElement::document;
        kmlReader reader(doc);

        if(!reader.read(&file)){
           qDebug() << "Parse Error in file:" << reader.errorString();
        }else {
            qDebug() <<"Doc id="<<doc->id();
            qDebug() <<"Doc name="<<doc->name();
            qDebug() <<"Doc snippet="<<doc->snippet();
            qDebug() <<"Doc maxline="<<doc->snippetmaxlines();
            qDebug() <<"Doc folders="<<doc->getFolders().size();
            qDebug() <<"Doc placemarks="<<doc->getFolders()[0].getPlacemarks().size();
            //qDebug() <<"Doc description="<<doc->getFolders()[0].getPlacemarks()[100].description();
            //qDebug() <<"Doc polyCoords="<<doc->getFolders()[0].getPlacemarks()[10].MultiGeometry().polygons()[0].outerBoundaryCoords();

        }
        file.close();
        //-----------
        QFile outFile("X:/Akshayan/GN Data/Survey Dpt/to_be_deleted.kml");
        if(!outFile.open(QFile::WriteOnly | QFile::Text)){
            qDebug()<<"Cannot Open OutFile:"<<"to_be_deleted.kml";
            return;
        }
        kmlWriter writer(doc);
        if(!writer.writeFile(&outFile)){
            qDebug() << "Write File error:";
        }else {
            qDebug() << "Write File Completed:";
        }
        outFile.close();
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "kmlQucik Examples...";
    usageReader();
    usageWriter();
    return a.exec();
}
