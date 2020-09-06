#include "kmlreader.h"
#include <QtGlobal>
#include <QDebug>
kmlReader::kmlReader(kmlElement::document *document)
{
    m_document = document;
}

bool kmlReader::read(QIODevice *device)
{
    reader.setDevice(device);
    //responsible for checking root element kml
    if(reader.readNextStartElement()){
        if(reader.name() == "kml"){
            readKML();
        }else {
            reader.raiseError(QObject::tr("Not a kml file"));
        }
    }
    return !reader.error();
}

QString kmlReader::errorString() const
{
    return QObject::tr("%1 in Line %2, column %3")
                .arg(reader.errorString())
                .arg(reader.lineNumber())
                .arg(reader.columnNumber());
}

void kmlReader::readKML()
{
    //to read the kml part
    //1.assert reader.name is kml
    //2. create an instance of kml, retrieve the values of attributes and set to kml
    // At this point kml object does not exist... Refer to readDocument() for code
    while(reader.readNextStartElement())   {
        if(reader.name() == "Document"){
            readDocument();
        }else {
            reader.skipCurrentElement();
        }
    }
}

void kmlReader::readDocument()
{
    //1.assert reader.name is Document
    //2. create an instance of Document, retrieve the values of attributes
    //3. get the elemnts in Document using while loop.
    Q_ASSERT(reader.isStartElement() &&
             reader.name() == "Document");
    readDocumentId();
    while(reader.readNextStartElement()){
        //Elements to be read in Document Element
        if(reader.name() == "name"){
            QString name = reader.readElementText();
            m_document->setName(name);
        }else if (reader.name() == "Snippet") {
            //qDebug() << "Found-> Document:snippet";
            if(reader.attributes().hasAttribute("maxLines")){
                //qDebug() << "Found-> Document:snippet *maxLines";
                int n = reader.attributes().value("maxLines").toInt();
                m_document->setSnippetmaxlines(n);
            }
            QString snippet = reader.readElementText();
            m_document->setSnippet(snippet);
        }else if (reader.name() == "Folder") {
            //qDebug() << "Found-> Document:Folder";
            kmlElement::folder* Folder = new kmlElement::folder;
            readFolder(Folder);
            m_document->addFolder(*Folder);
        }else {
            reader.skipCurrentElement();
        }
    }

}

void kmlReader::readDocumentId()
{
    //retrieve the "id" attribute in Element Document
    //NOTE: if the element has xsi:scheemaLocation
    //  namespace decleration, delete 'xsi:' part //low
    //  else parse error xsi prefix was not declared
    Q_ASSERT(reader.name() == "Document" &&
             reader.attributes().hasAttribute("id"));
    QString id = reader.attributes().value("id").toString();
    m_document->setId(id);
}

void kmlReader::readFolder(kmlElement::folder *Folder)
{
    Q_ASSERT(reader.isStartElement() &&
             reader.name() == "Folder");
    if(reader.attributes().hasAttribute("id")){
        QString id = reader.attributes().value("id").toString();
        Folder->setId(id);
        //qDebug() << "Found-> Document:Folder *id"<<id;
    }
    while(reader.readNextStartElement()){
        //qDebug() << "Read Folder WhileLoop:"<<reader.name();
        if(reader.name() == "name"){
            QString name = reader.readElementText();
            Folder->setName(name);
            //qDebug() << "Found-> Document:Folder:name"<<name;
        }else if (reader.name() == "Snippet") {
            if(reader.attributes().hasAttribute("maxLines")){
                int n = reader.attributes().value("maxLines").toInt();
                Folder->setSnippetmaxlines(n);
                //qDebug() << "Found-> Document:Folder:snippet *maxLines"<<n;
            }
            QString snippet = reader.readElementText();
            Folder->setSnippet(snippet);
            //qDebug() << "Found-> Document:Folder:snippet"<<snippet;
        }else if(reader.name() == "Placemark"){
            kmlElement::placemark* Placemark = new kmlElement::placemark;
            readPlacemark(Placemark);
            Folder->addPlacemark(*Placemark);
            //qDebug() << "Placemark:"<<Placemark->name();
        }else {
            reader.skipCurrentElement();
        }
    }//while loop
}

void kmlReader::readPlacemark(kmlElement::placemark* Placemark)
{
    Q_ASSERT(reader.isStartElement() &&
             reader.name() == "Placemark");
    if(reader.attributes().hasAttribute("id")){
        QString id = reader.attributes().value("id").toString();
        Placemark->setId(id);
        qDebug()<<" Placemark:"<<id;
    }
    while (reader.readNextStartElement()) {
        if(reader.name() == "name"){
            QString name = reader.readElementText();
            Placemark->setName(name);
        }else if (reader.name() == "Snippet") {
            if(reader.attributes().hasAttribute("maxLines")){
                int n = reader.attributes().value("maxLines").toInt();
                Placemark->setSnippetmaxlines(n);
            }
            QString snippet = reader.readElementText();
            Placemark->setSnippet(snippet);
        }else if (reader.name() == "description") {
            QString description = reader.readElementText();
            Placemark->setDescription(description);
        }else if (reader.name() == "styleUrl") {
            QString styleUrl = reader.readElementText();
            Placemark->setStyleUrl(styleUrl);
        }else if (reader.name() == "styleUrl") {
            QString styleUrl = reader.readElementText();
            Placemark->setStyleUrl(styleUrl);
        }else if (reader.name() == "MultiGeometry") {
            kmlElement::multigeometry* Multigeometry = new kmlElement::multigeometry;
            readMultiGeometry(Multigeometry);
            Placemark->setMultiGeometry(*Multigeometry);
        }
        else {
            reader.skipCurrentElement();
        }
    }//while loop
}

void kmlReader::readMultiGeometry(kmlElement::multigeometry *MultiGeometry)
{
    Q_ASSERT(reader.isStartElement() &&
             reader.name() == "MultiGeometry");
    while(reader.readNextStartElement()){
        if(reader.name() == "Polygon"){
            kmlElement::polygon* Polygon = new kmlElement::polygon;
            readPolygon(Polygon);
            MultiGeometry->addPolygon(*Polygon);
        }
        else {
            reader.skipCurrentElement();
        }
    }//while loop
}

void kmlReader::readPolygon(kmlElement::polygon *Polygon)
{
    Q_ASSERT(reader.isStartElement() &&
             reader.name() == "Polygon");
    while (reader.readNextStartElement()) {
        if(reader.name() == "outerBoundaryIs"){
            reader.readNextStartElement();
            if(reader.name() == "LinearRing"){
                reader.readNextStartElement();
                if(reader.name() == "coordinates"){
                    QString* coord = new QString;
                    readCoordinate(coord);//reads element
                    Polygon->setOuterBoundaryCoords(*coord);
                }else {
                    reader.skipCurrentElement();
                }//coordinates
                reader.skipCurrentElement();//get out of LinearRing
            }else {
                reader.skipCurrentElement();
            }//LinearRing
            reader.skipCurrentElement();//get out of outerBoundaryIs
        }else {
            reader.skipCurrentElement();
        }//outerBoundaryIs

    }//while loop
}

void kmlReader::readCoordinate(QString *coord)
{
    Q_ASSERT(reader.isStartElement() &&
             reader.name() == "coordinates");
    (*coord) = reader.readElementText();

}
