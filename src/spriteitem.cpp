#include "spriteitem.h"

#include "gamescene.h"
#include "spriteanimationitem.h"
#include "animationchangeevent.h"
#include "animationtransition.h"

#include <QDebug>


void SpriteItem::append_animation(QDeclarativeListProperty<SpriteAnimationItem> *list, SpriteAnimationItem *animation)
{
    SpriteItem *spriteItem = qobject_cast<SpriteItem *>(list->object);

    if (spriteItem) {
        GameSprite *sprite = animation->sprite();
        sprite->setVisible(false);
        sprite->setParentItem(spriteItem);
        spriteItem->m_states.insert(animation->name(), animation);
    }
}

SpriteItem::SpriteItem(GameScene *parent)
    : GameItem(parent)
    , m_stateMachine(0)
    , m_stateGroup(0)
{
}

QDeclarativeListProperty<SpriteAnimationItem> SpriteItem::animations() const
{
    return QDeclarativeListProperty<SpriteAnimationItem>(const_cast<SpriteItem *>(this), 0, &SpriteItem::append_animation);
}

QString SpriteItem::animation() const
{
    return m_animation;
}

void SpriteItem::setAnimation(const QString &animation, const bool &force)
{
    if (force || (m_animation != animation)) {
        m_animation = animation;

        if (!m_stateMachine)
            initializeMachine();

        if (m_stateMachine && m_stateMachine->isRunning())
            m_stateMachine->postEvent(new AnimationChangeEvent(m_animation));

        emit animationChanged();
    }
}

GameSprite *SpriteItem::currentSprite() const
{
    return m_currentSprite;
}

void SpriteItem::setCurrentSprite(GameSprite *currentSprite)
{
    if (m_currentSprite != currentSprite) {
        if (m_currentSprite)
            m_currentSprite->setVisible(false);

        m_currentSprite = currentSprite;

        if (m_currentSprite)
            m_currentSprite->setVisible(true);

        emit currentSpriteChanged();
    }
}

SpriteAnimation *SpriteItem::currentSpriteAnimation() const
{
    return m_currentSpriteAnimation;
}

void SpriteItem::setCurrentSpriteAnimation(SpriteAnimation *currentSpriteAnimation)
{
    if (m_currentSpriteAnimation != currentSpriteAnimation) {
        if (m_currentSpriteAnimation)
            m_currentSpriteAnimation->stop();

        m_currentSpriteAnimation = currentSpriteAnimation;
        m_currentSpriteAnimation->setSprite(m_currentSprite);

        if (m_currentSpriteAnimation)
            m_currentSpriteAnimation->start();

        emit currentSpriteAnimationChanged();
    }
}

void SpriteItem::initializeMachine()
{
    m_stateMachine= new QStateMachine;
    m_stateGroup = new QState(QState::ParallelStates);

    SpriteAnimationItem *animation;
    foreach (animation, m_states.values()) {
        AnimationTransition *transition = new AnimationTransition(this, animation);
        animation->setParent(m_stateGroup);
        animation->addTransition(transition);
    }

    m_stateMachine->addState(m_stateGroup);
    m_stateMachine->setInitialState(m_stateGroup);

    connect(m_stateMachine, SIGNAL(started()), this, SLOT(initializeAnimation()));

    m_stateMachine->start();
}

void SpriteItem::initializeAnimation()
{
    if (m_animation != QString())
        setAnimation(m_animation, true);
}
