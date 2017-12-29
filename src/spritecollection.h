#ifndef SPRITECOLLECTION_H
#define SPRITECOLLECTION_H

#include <QObject>
#include <QHash>
#include <QMultiHash>
#include <QUrl>
#include <QPixmap>

class Sprite;
class AnimatedSprite;

class SpriteCollection : public QObject
{
    Q_OBJECT
public:
    static SpriteCollection &instance();

    QPixmap addSprite(Sprite *sprite);
    QPixmap addSprite(AnimatedSprite *sprite);
    void removeSprite(Sprite *sprite);
    void removeSprite(AnimatedSprite *sprite);
private:
    static SpriteCollection *m_instance;
    QHash<QUrl, QPixmap> m_spritesheets;
    QMultiHash<QUrl, Sprite *> m_sprites;
    QMultiHash<QUrl, AnimatedSprite *> m_animatedSprites;

    explicit SpriteCollection(QObject *parent = nullptr);
};

#endif // SPRITECOLLECTION_H
