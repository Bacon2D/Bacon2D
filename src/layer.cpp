#include "layer.h"

//! Class constructor
/*!
 * \param tiled layer type
 * \param factor layer update factor
 * \sa setTiled() and setFactor()
 */
Layer::Layer(bool tiled, int factor)
{
    m_tiled = tiled;
    m_factor = factor;
}

//! Class destructor
Layer::~Layer()
{
    m_pixmaps.clear();
}

//! Stores the layer type (tiled or plane)
/*!
 * \param tiled true for tiled, false for plane
 */
void Layer::setTiled(bool tiled)
{
    if (m_tiled != tiled)
        m_tiled = tiled;
}

//! Gets the layer type
/*!
 * \return true if tiled, false if plane
 */
bool Layer::tiled() const
{
    return m_tiled;
}

//! Stores the layer update factor
/*!
 * \param factor the factor value
 */
void Layer::setFactor(float factor)
{
    if (m_factor != factor)
        m_factor = factor;
}

//! Gets the layer update factor
/*!
 * \return layer update factor
 */
float Layer::factor() const
{
    return m_factor;
}

//! Adds a tile on the list
/*!
 * \param pix the pixmap to append on the list
 * \return the list actual size or -1 if the layer can not accept tiled pixmaps
 * \sa setPixmap()
 */
int Layer::addTile(const QPixmap &pix)
{
    if (m_tiled){
        m_pixmaps.append(pix);
        return m_pixmaps.size();
    }

    return -1;
}

//! Gets a tile from the list
/*!
 * \param pos the tile position on the list
 * \return the tile pixmap of position pos on the list or null, if none
 * \sa getPixmap()
 */
QPixmap Layer::getTile(int pos) const
{
    return m_pixmaps.at(pos);
}

//! Gets the tiles pixmap list size
/*!
 * \return the tiles pixmap list size
 */
int Layer::count() const
{
    return m_pixmaps.size();
}

//! Stores a pixmap on the list (this will the only pixmap on the list)
/*!
 * \param pix the pixmao to store on the list
 * \return 1 if ok, -1 if the layer accept only tiled pixmaps
 * \sa addTile()
 */
int Layer::setPixmap(const QPixmap &pix)
{
    if (!m_tiled){
        m_pixmaps.insert(0, pix);
        return 1;
    }

    return -1;
}

//! Gets the pixmap stored on the list
/*!
 * \return the stored pixmap (full lenght), or null if none
 * \sa getTile()
 */
QPixmap Layer::getPixmap() const
{
    return m_pixmaps.at(0);
}
