#ifndef TMXCELL
#define TMXCELL

#include "tmxlayer.h"
#include "tmxcell.h"
#include "tmxtile.h"

#include <libtiled/tilelayer.h>
#include <QDebug>

class TMXCell : public QObject
{
    Q_OBJECT
public:
    explicit TMXCell(const Tiled::Cell &cell, QObject *parent = 0)   : QObject(parent), m_cell(cell.tile()){
        m_cell.setFlippedAntiDiagonally(cell.flippedAntiDiagonally());
        m_cell.setFlippedHorizontally(cell.flippedHorizontally());
        m_cell.setFlippedVertically(cell.flippedVertically());
    }
    TMXCell(const TMXCell &other) { setCell(other.cell()); }
    TMXCell &operator=(const TMXCell &other) { setCell(other.cell()); return *this; }

    Tiled::Cell cell() const { return m_cell; }
    void setCell(const Tiled::Cell &cell) { m_cell = cell; }

    bool isEmpty() const { return m_cell.isEmpty(); }
    
    bool flippedHorizontally() const { return m_cell.flippedHorizontally(); }
    bool flippedVertically() const { return m_cell.flippedVertically(); }
    bool flippedAntiDiagonally() const { return m_cell.flippedAntiDiagonally(); }

    TMXTile tile() const { return TMXTile(m_cell.tile()); }
private:
    Tiled::Cell m_cell;
};

#endif // TMXCELL

