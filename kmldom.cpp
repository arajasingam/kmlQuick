#include "kmldom.h"

namespace kmlElement {

/********************************** Start of Class style ***************************************/
QString style::id() const
{
    return m_id;
}

void style::setId(const QString &id)
{
    m_id = id;
}

QString style::IconStyle() const
{
    return m_IconStyle;
}

void style::setIconStyle(const QString &IconStyle)
{
    m_IconStyle = IconStyle;
}

QString style::LabelStyle() const
{
    return m_LabelStyle;
}

void style::setLabelStyle(const QString &LabelStyle)
{
    m_LabelStyle = LabelStyle;
}

QString style::LineStyle() const
{
    return m_LineStyle;
}

void style::setLineStyle(const QString &LineStyle)
{
    m_LineStyle = LineStyle;
}

QString style::PolyStyle() const
{
    return m_PolyStyle;
}

void style::setPolyStyle(const QString &PolyStyle)
{
    m_PolyStyle = PolyStyle;
}

QString style::BalloonStyle() const
{
    return m_BalloonStyle;
}

void style::setBalloonStyle(const QString &BalloonStyle)
{
    m_BalloonStyle = BalloonStyle;
}

QString style::ListStyle() const
{
    return m_ListStyle;
}

void style::setListStyle(const QString &ListStyle)
{
    m_ListStyle = ListStyle;
}

QString style::styleContent() const
{
    return m_styleContent;
}

void style::setStyleContent(const QString &styleContent)
{
    m_styleContent = styleContent;
}
/********************************** End of Class style ***************************************/

/********************************** Start of Class stylemap ***************************************/
QString stylemap::normalpairstyleurl() const
{
    return m_normalpairstyleurl;
}

void stylemap::setNormalpairstyleurl(const QString &normalpairstyleurl)
{
    m_normalpairstyleurl = normalpairstyleurl;
}

QString stylemap::highlightpairstyleurl() const
{
    return m_highlightpairstyleurl;
}

void stylemap::setHighlightpairstyleurl(const QString &highlightpairstyleurl)
{
    m_highlightpairstyleurl = highlightpairstyleurl;
}
/********************************** End of Class stylemap ***************************************/

/********************************** Start of Class polygon ***************************************/
polygon::polygon()
{
    m_id = "poly_0";
    m_altitudeMode = "absolute";
    m_extrude = false;
}

QString polygon::id() const
{
    return m_id;
}

void polygon::setId(const QString &id)
{
    m_id = id;
}

QString polygon::altitudeMode() const
{
    return m_altitudeMode;
}

void polygon::setAltitudeMode(const QString &altitudeMode)
{
    m_altitudeMode = altitudeMode;
}

QString polygon::outerBoundaryCoords() const
{
    return m_outerBoundaryCoords;
}

void polygon::setOuterBoundaryCoords(const QString &outerBoundaryCoords)
{
    m_outerBoundaryCoords = outerBoundaryCoords;
}

bool polygon::extrude() const
{
    return m_extrude;
}

void polygon::setExtrude(bool extrude)
{
    m_extrude = extrude;
}
/********************************** End of Class polygon ***************************************/

/********************************** Start of Class multigeometry ***************************************/
QList<polygon> multigeometry::polygons() const
{
    return m_polygons;
}

void multigeometry::addPolygon(polygon poly)
{
    m_polygons.push_back(poly);
}
/********************************** End of Class multigeometry ***************************************/

/********************************** Start of Class placemark ***************************************/
placemark::placemark()
{
    m_id ="p_00";
    m_name = "placemark_name";
    m_snippet = "";
    m_snippetmaxlines =0;
    m_description = "";
    m_styleUrl = "";
}

QString placemark::id() const
{
    return m_id;
}

void placemark::setId(const QString &id)
{
    m_id = id;
}

QString placemark::snippet() const
{
    return m_snippet;
}

void placemark::setSnippet(const QString &snippet)
{
    m_snippet = snippet;
}

int placemark::snippetmaxlines() const
{
    return m_snippetmaxlines;
}

void placemark::setSnippetmaxlines(int snippetmaxlines)
{
    m_snippetmaxlines = snippetmaxlines;
}

QString placemark::description() const
{
    return m_description;
}

void placemark::setDescription(const QString &description)
{
    m_description = description;
}

QString placemark::styleUrl() const
{
    return m_styleUrl;
}

void placemark::setStyleUrl(const QString &styleUrl)
{
    m_styleUrl = styleUrl;
}

multigeometry placemark::MultiGeometry() const
{
    return m_MultiGeometry;
}

void placemark::setMultiGeometry(const multigeometry &MultiGeometry)
{
    m_MultiGeometry = MultiGeometry;
}

polygon placemark::Polygon() const
{
    return m_Polygon;
}

void placemark::setPolygon(const polygon &Polygon)
{
    m_Polygon = Polygon;
}

QString placemark::name() const
{
    return m_name;
}

void placemark::setName(const QString &name)
{
    m_name = name;
}
/********************************** End of Class placemark ***************************************/

/********************************** Start of Class folder ***************************************/
folder::folder()
{
    //All Member variables can be modified After
    m_id ="f_01";//default folder id
    m_name = "folder_name";//default folder name
    m_snippet = "";//defauilt folder snippet
    m_snippetmaxlines = 0;//default snippet maxLines

}

QString folder::id() const
{
    return m_id;
}

void folder::setId(const QString &id)
{
    m_id = id;
}

QString folder::name() const
{
    return m_name;
}

void folder::setName(const QString &name)
{
    m_name = name;
}

QString folder::snippet() const
{
    return m_snippet;
}

void folder::setSnippet(const QString &snippet)
{
    m_snippet = snippet;
}

int folder::snippetmaxlines() const
{
    return m_snippetmaxlines;
}

void folder::setSnippetmaxlines(int snippetmaxlines)
{
    m_snippetmaxlines = snippetmaxlines;
}

QList<placemark> folder::getPlacemarks() const
{
    return placemarks;
}

void folder::addPlacemark(placemark p)
{
    placemarks.push_back(p);
}
/********************************** End of Class folder ***************************************/

/********************************** Start of Class document ***************************************/
document::document()
{
    //All Member variables can be modified After
    m_id = "doc_01";//default id
    m_name = "doc_name";//default name
    m_snippet="";//default snippet
    m_snippetmaxlines =0;//default snippet maxLines attribute

}

QString document::id() const
{
    return m_id;
}

void document::setId(const QString &id)
{
    m_id = id;
}

QString document::name() const
{
    return m_name;
}

void document::setName(const QString &name)
{
    m_name = name;
}

QString document::snippet() const
{
    return m_snippet;
}

void document::setSnippet(const QString &snippet)
{
    m_snippet = snippet;
}

int document::snippetmaxlines() const
{
    return m_snippetmaxlines;
}

void document::setSnippetmaxlines(int snippetmaxlines)
{
    m_snippetmaxlines = snippetmaxlines;
}

QList<placemark> document::getPlacemarks() const
{
    return placemarks;
}

void document::addPlacemark(placemark p)
{
    placemarks.push_back(p);
}

QList<folder> document::getFolders() const
{
    return folders;
}

void document::addFolder(folder f)
{
    folders.push_back(f);
}


/********************************** End of Class document ***************************************/


}//namespace kmlElement


namespace kmlFactory{


}//namespace kmlFactory
