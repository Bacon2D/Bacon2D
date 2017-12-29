#include "spritecollection.h"
#include <QCoreApplication>
#include "sprite.h"
#include "animatedsprite.h"

SpriteCollection *SpriteCollection::m_instance = nullptr;

SpriteCollection::SpriteCollection(QObject *parent) :
    QObject(parent)
{

}

SpriteCollection &SpriteCollection::instance()
{
    if (m_instance == nullptr) {
        m_instance = new SpriteCollection;
        connect(qApp, &QCoreApplication::aboutToQuit, m_instance, &SpriteCollection::deleteLater);
    }

    return *m_instance;
}

QPixmap SpriteCollection::addSprite(Sprite *sprite)
{
    QPixmap pixmap;

    if (sprite && !sprite->source().isEmpty()) {
        if (m_spritesheets.contains(sprite->source()))
            pixmap = m_spritesheets.value(sprite->source());
        else {
            if (sprite->source().url().startsWith("qrc:/"))
                pixmap = QPixmap(sprite->source().url().replace(QString("qrc:/"), QString(":/")));
            else
                pixmap = QPixmap(sprite->source().toLocalFile());
        }

        if (pixmap.isNull())
            qCritical() << QString("Bacon2D>>Image \'%1\' failed to load!").arg(sprite->source().url());
        else {
            m_spritesheets.insert(sprite->source(), pixmap);
            m_sprites.insert(sprite->source(), sprite);
        }
    }

    return pixmap;
}

QPixmap SpriteCollection::addSprite(AnimatedSprite *sprite)
{
    QPixmap pixmap;

    if (sprite && !sprite->source().isEmpty()) {
        if (m_spritesheets.contains(sprite->source()))
            pixmap = m_spritesheets.value(sprite->source());
        else {
            if (sprite->source().url().startsWith("qrc:/"))
                pixmap = QPixmap(sprite->source().url().replace(QString("qrc:/"), QString(":/")));
            else
                pixmap = QPixmap(sprite->source().toLocalFile());
        }

        if (pixmap.isNull())
            qCritical() << QString("Bacon2D>>Image \'%1\' failed to load!").arg(sprite->source().url());
        else {
            m_spritesheets.insert(sprite->source(), pixmap);
            m_animatedSprites.insert(sprite->source(), sprite);
        }
    }

    return pixmap;
}

void SpriteCollection::removeSprite(Sprite *sprite)
{
    if (sprite && m_sprites.contains(sprite->source())) {
        m_sprites.remove(sprite->source(), sprite);

        if (!m_sprites.contains(sprite->source()))
            m_spritesheets.remove(sprite->source());
    }
}

void SpriteCollection::removeSprite(AnimatedSprite *sprite)
{
    if (sprite && m_animatedSprites.contains(sprite->source())) {
        m_animatedSprites.remove(sprite->source(), sprite);

        if (!m_animatedSprites.contains(sprite->source()))
            m_spritesheets.remove(sprite->source());
    }
}
