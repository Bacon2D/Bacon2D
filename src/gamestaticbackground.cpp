#include "gamestaticbackground.h"

GameStaticBackground::GameStaticBackground(GameBaseBackground *parent)
    : GameBaseBackground(parent)
{
}

GameStaticBackground::~GameStaticBackground()
{
}

void GameStaticBackground::updateTiles()
{
    if ((boundingRect().width() == 0) || (boundingRect().height() == 0))
        return;

    Layer layer(false);
    QPixmap pix(source());
    layer.setPixmap(pix);

    m_layers.append(layer);
    update();
}

void GameStaticBackground::paint(QPainter *painter)
{
    painter->drawPixmap(0, 0, m_layers.at(0).getPixmap());
}
