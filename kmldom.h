// Created by Akshayan Rajasingam
// Version 1.0 (2020.09.01)
//

//Quick Classes to reference .kml DOM.
//  It only contains the elements that I am interested in right now
//  I will update it in the future as my useage needs change.
#ifndef KMLDOM_H
#define KMLDOM_H
#include <QString>
#include <QList>

namespace kmlElement {


class style
{
public:
    style();
    QString id() const;
    void setId(const QString &id);

    QString IconStyle() const;
    void setIconStyle(const QString &IconStyle);

    QString LabelStyle() const;
    void setLabelStyle(const QString &LabelStyle);

    QString LineStyle() const;
    void setLineStyle(const QString &LineStyle);

    QString PolyStyle() const;
    void setPolyStyle(const QString &PolyStyle);

    QString BalloonStyle() const;
    void setBalloonStyle(const QString &BalloonStyle);

    QString ListStyle() const;
    void setListStyle(const QString &ListStyle);

    QString styleContent() const;
    void setStyleContent(const QString &styleContent);

private:
    QString m_id,m_IconStyle,m_LabelStyle,m_LineStyle,m_PolyStyle,m_BalloonStyle,m_ListStyle;
    QString m_styleContent;

};
//---***---***---***---***---***---***---***
class stylemap
{
public:
    QString normalpairstyleurl() const;
    void setNormalpairstyleurl(const QString &normalpairstyleurl);

    QString highlightpairstyleurl() const;
    void setHighlightpairstyleurl(const QString &highlightpairstyleurl);

    static inline QString styleMapElement(){ return QStringLiteral("StyleMap"); }
    static inline QString idAttribute(){ return QStringLiteral("id"); }

private:
    QString m_normalpairstyleurl,m_highlightpairstyleurl;
};
//---***---***---***---***---***---***---***
class polygon
{
public:
    polygon();

    QString id() const;
    void setId(const QString &id);

    QString altitudeMode() const;
    void setAltitudeMode(const QString &altitudeMode);

    QString outerBoundaryCoords() const;
    void setOuterBoundaryCoords(const QString &outerBoundaryCoords);

    bool extrude() const;
    void setExtrude(bool extrude);

    static inline QString multiGeometryElement(){ return QStringLiteral("Polygon"); }
    static inline QString idAttribute(){ return QStringLiteral("id"); }

private:
    QString m_id,m_altitudeMode;
    QString m_outerBoundaryCoords;//??
    bool m_extrude;
    //Future Include QList of Innerboundry Coords, polygon can have multiple of these. refer to kml documentation
};
//---***---***---***---***---***---***---***
class multigeometry
{
public:
    QList<polygon> polygons() const;
    void addPolygon(polygon poly);

    static inline QString multiGeometryElement(){ return QStringLiteral("MultiGeometry"); }

private:
    //can contain <LineString> and others, but for now
    QList<polygon> m_polygons;
};
//---***---***---***---***---***---***---***
class placemark
{
public:
    placemark();

    QString id() const;
    void setId(const QString &id);

    QString snippet() const;
    void setSnippet(const QString &snippet);

    int snippetmaxlines() const;
    void setSnippetmaxlines(int snippetmaxlines);

    QString description() const;
    void setDescription(const QString &description);

    QString styleUrl() const;
    void setStyleUrl(const QString &styleUrl);

    multigeometry MultiGeometry() const;
    void setMultiGeometry(const multigeometry &MultiGeometry);

    polygon Polygon() const;
    void setPolygon(const polygon &Polygon);

    QString name() const;
    void setName(const QString &name);

    static inline QString placemarkElement(){ return QStringLiteral("Placemark"); }
    static inline QString idAttribute(){ return QStringLiteral("id"); }
    static inline QString nameElement(){ return QStringLiteral("name"); }
    static inline QString snippetElement(){ return QStringLiteral("Snippet"); }
    static inline QString snippetMaxLinesAttribute(){ return QStringLiteral("maxLines"); }
    static inline QString descriptionElement(){ return QStringLiteral("description"); }
    static inline QString styleurlElement(){ return QStringLiteral("styleUrl"); }

private:
    QString m_id,m_name,m_snippet,m_description,m_styleUrl;
    int m_snippetmaxlines;
    //placemark can have multigeometry, polygon, point
    multigeometry m_MultiGeometry;
    polygon m_Polygon;

};
//---***---***---***---***---***---***---***
class folder
{
public:
    folder();
    QString id() const;
    void setId(const QString &id);

    QString name() const;
    void setName(const QString &name);

    QString snippet() const;
    void setSnippet(const QString &snippet);

    int snippetmaxlines() const;
    void setSnippetmaxlines(int snippetmaxlines);

    QList<placemark> getPlacemarks() const;
    void addPlacemark(placemark p);

    static inline QString folderElement(){ return QStringLiteral("Folder"); }
    static inline QString idAttribute(){ return QStringLiteral("id"); }
    static inline QString nameElement(){ return QStringLiteral("name"); }
    static inline QString snippetElement(){ return QStringLiteral("Snippet"); }
    static inline QString snippetMaxLinesAttribute(){ return QStringLiteral("maxLines"); }

private:
    QString m_id,m_name,m_snippet;
    int m_snippetmaxlines;
    QList<placemark> placemarks;
};

//---***---***---***---***---***---***---***
class document
{
public:
    document();

    QString id() const;
    void setId(const QString &id);

    QString name() const;
    void setName(const QString &name);

    QString snippet() const;
    void setSnippet(const QString &snippet);

    int snippetmaxlines() const;
    void setSnippetmaxlines(int snippetmaxlines);

    QList<placemark> getPlacemarks() const;
    void addPlacemark(placemark p);

    QList<folder> getFolders() const;
    void addFolder(folder f);

    static inline QString documantElement(){ return QStringLiteral("Document"); }
    static inline QString idAttribute(){ return QStringLiteral("id"); }
    static inline QString nameElement(){ return QStringLiteral("name"); }
    static inline QString snippetElement(){ return QStringLiteral("Snippet"); }
    static inline QString snippetMaxLinesAttribute(){ return QStringLiteral("maxLines"); }

private:
    QString m_id,m_name,m_snippet;
    int m_snippetmaxlines;
    QList<placemark>placemarks;
    QList<folder>folders;
};
}//namespace kmlElement


namespace kmlFactory{
//This namespace is a collection of functions that will initialize all the kml elements safely
//kml elements should be created through kmlfactory.
kmlElement::document makedocument();

}//namespace kmlFactory

#endif // KMLDOM_H
