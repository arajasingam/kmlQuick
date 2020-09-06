// Created by Akshayan Rajasingam
// Version 1.0 (2020.09.01)
//

//Qucik class to write .kml files with data using QXmlStreamWriter
#ifndef KMLWRITER_H
#define KMLWRITER_H
#include "kmldom.h"
#include <QXmlStreamWriter>
#include <QIODevice>
class kmlWriter
{
public:
    explicit kmlWriter(const kmlElement::document* Document);
    bool writeFile(QIODevice* device);
private:
    QXmlStreamWriter writer;
    const kmlElement::document *document;

    void writeDocument();
    void writeFolder(kmlElement::folder *Folder);
    void writePlacemark(kmlElement::placemark *Placemark);
};

#endif // KMLWRITER_H
