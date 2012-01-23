#ifndef _LAYER_H_
#define _LAYER_H

#include <QList>
#include <QPixmap>

//! A container class to act as layer
class Layer
{

public:
    typedef QList<Layer> LayerList; //! A layer list based on QList

    Layer(bool tiled = true, int factor = 1.0);
    ~Layer();

    void setTiled(bool tiled); // XXX use enum?
    bool tiled() const;

    void setFactor(float factor);
    float factor() const;

    int addTile(const QPixmap &pix);
    QPixmap getTile(int pos) const;
    int count() const;

    int setPixmap(const QPixmap &pix);
    QPixmap getPixmap();

private:
    QList<QPixmap> m_pixmaps; // can be a list of tiles or a single image
    bool m_tiled;
    float m_factor;
};

#endif /* _LAYER */
