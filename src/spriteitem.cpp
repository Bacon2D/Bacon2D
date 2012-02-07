#include "spriteitem.h"

#include "gamescene.h"
#include "spritesheet.h"
#include "spriteanimationitem.h"
#include "animationchangeevent.h"
#include "animationtransition.h"

void SpriteItem::append_animation(QDeclarativeListProperty<SpriteAnimationItem> *list, SpriteAnimationItem *animation)
{
    SpriteItem *spriteItem = qobject_cast<SpriteItem *>(list->object);

    if (spriteItem) {
        spriteItem->m_states.insert(animation->name(), animation);
        animation->spriteSheet()->setParentItem(spriteItem);
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
        if (m_animation != QString()) {
            SpriteAnimationItem *animationItem = m_states[m_animation];
            animationItem->setRunning(false);
            animationItem->setVisible(false);
        }
        m_animation = animation;

        if (!m_stateMachine)
            initializeMachine();

        if (m_stateMachine && m_stateMachine->isRunning())
            m_stateMachine->postEvent(new AnimationChangeEvent(m_animation));

        emit animationChanged();
    }
}

void SpriteItem::initializeMachine()
{
    m_stateMachine= new QStateMachine;
    m_stateGroup = new QState(QState::ParallelStates);

    SpriteAnimationItem *animation;
    foreach (animation, m_states.values()) {
        AnimationTransition *transition = new AnimationTransition(animation);
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
