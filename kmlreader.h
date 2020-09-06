// Created by Akshayan Rajasingam
// Version 1.0 (2020.09.01)
//      used QT Tutorials at walletfox.com as reference(https://www.walletfox.com/course/qxmlstreamreaderexample.php)


//Quick class to read and extract data from a .kml using QXmlStreamReader
#ifndef KMLREADER_H
#define KMLREADER_H

#include "kmldom.h"
#include <QIODevice>
#include <QXmlStreamReader>

class kmlReader
{
public:
    kmlReader(kmlElement::document* document);
    bool read(QIODevice *device);
    QString errorString() const;
private:
    QXmlStreamReader reader;
    kmlElement::document* m_document;

    void readKML();
    void readDocument();
    void readDocumentId();
    void readFolder(kmlElement::folder* Folder);
    void readPlacemark(kmlElement::placemark* Placemark);
    void readMultiGeometry(kmlElement::multigeometry* MultiGeometry);
    void readPolygon(kmlElement::polygon* Polygon);
    void readCoordinate(QString* coord);
};



#endif // KMLREADER_H
