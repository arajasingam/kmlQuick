#include "kmlwriter.h"

kmlWriter::kmlWriter(const kmlElement::document *Document)
    :document(Document)
{
    writer.setAutoFormatting(true);
}

bool kmlWriter::writeFile(QIODevice *device)
{
    writer.setDevice(device);

    writer.writeStartDocument("1.0");
    //writer.writeDTD("<!DOCTYPE xbel>");
    writer.writeComment("This is a Comment");
    writer.writeStartElement("kml");
    writeDocument();
    writer.writeEndDocument();
    return true;
}

void kmlWriter::writeDocument()
{
    writer.writeStartElement(document->documantElement());
    writer.writeAttribute(document->idAttribute(),document->id());
    writer.writeTextElement(document->nameElement(),document->name());

    writer.writeStartElement(document->snippetElement());
    writer.writeAttribute(document->snippetMaxLinesAttribute(),"1");
    writer.writeCharacters("a bunch of text");
    writer.writeEndElement();//Snippet
    //write Folders
    for (int i=0; i<document->getFolders().size();++i) {
        writeFolder(&document->getFolders()[i]);
    }
    //write Placemarks
    for (int i=0; i<document->getPlacemarks().size();++i) {
        writePlacemark(&document->getPlacemarks()[i]);
    }


}

void kmlWriter::writeFolder(kmlElement::folder *Folder)
{
    writer.writeStartElement(Folder->folderElement());
    writer.writeAttribute(Folder->idAttribute(),Folder->id());
    writer.writeTextElement(Folder->nameElement(),Folder->name());
    writer.writeStartElement(Folder->snippetElement());
    writer.writeAttribute(Folder->snippetMaxLinesAttribute(),QString::number(Folder->snippetmaxlines()));
    writer.writeCharacters("folder sub head");
    writer.writeEndElement();//Snippet
    for (int i=0; i<Folder->getPlacemarks().size(); ++i) {
        writePlacemark(&Folder->getPlacemarks()[i]);
    }
}

void kmlWriter::writePlacemark(kmlElement::placemark *Placemark)
{
    writer.writeStartElement(Placemark->placemarkElement());
    writer.writeAttribute(Placemark->idAttribute(),Placemark->id());
    writer.writeTextElement(Placemark->nameElement(),Placemark->name());
    writer.writeStartElement(Placemark->snippetElement());
    writer.writeAttribute(Placemark->snippetMaxLinesAttribute(),QString::number(Placemark->snippetmaxlines()));
    writer.writeCharacters("Placemark sub head");
    writer.writeEndElement();//Snippet

    writer.writeStartElement(Placemark->descriptionElement());
    writer.writeCDATA(Placemark->description());
    writer.writeEndElement();
    writer.writeTextElement(Placemark->styleurlElement(),Placemark->styleUrl());
}

