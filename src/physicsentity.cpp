#include "physicsentity.h"
#include "box2dbody.h"

PhysicsEntity::PhysicsEntity(QQuickItem *parent)
    :Entity(parent)
{
    setTransformOrigin(QQuickItem::TopLeft);
}

void PhysicsEntity::setBody(Body *body)
{
    if(body != mBody){
        mBody = body;
        emit bodyChanged(mBody);
    }
}

void PhysicsEntity::applyForce(QPointF force, QPointF point)
{
    if(mBody){
        mBody->applyForce(force,point);
    }
}

void PhysicsEntity::applyForceToCenter(QPointF force)
{
    if(mBody){
        mBody->applyForceToCenter(force);
    }
}

void PhysicsEntity::applyTorque(qreal torque)
{
    if(mBody){
        mBody->applyTorque(torque);
    }
}

void PhysicsEntity::applyLinearImpulse(QPointF impulse, QPointF point)
{
    if(mBody){
        mBody->applyLinearImpulse(impulse,point);
    }
}

void PhysicsEntity::applyAngularImpulse(qreal torque)
{
    if(mBody){
        mBody->applyAngularImpulse(torque);
    }
}

QPointF PhysicsEntity::getWorldCenter()
{
    if(mBody){
        return mBody->getWorldCenter();
    }else{
        return QPointF();
    }
}

QPointF PhysicsEntity::getLocalCenter()
{
    if(mBody){
        return mBody->getLocalCenter();
    }else{
        return QPointF();
    }

}

float PhysicsEntity::getMass()
{
    if(mBody){
        return mBody->getMass();
    }else{
        return 0.0f;
    }
}

void PhysicsEntity::resetMassData()
{
    if(mBody){
        mBody->resetMassData();
    }
}

float PhysicsEntity::getInertia()
{
    if(mBody){
        return mBody->getInertia();
    }else{
        return 0.0f;
    }
}

QPointF PhysicsEntity::toWorldPoint(QPointF localPoint)
{
    if(mBody){
        return mBody->toWorldPoint(localPoint);
    }else{
        return QPointF();
    }
}

QPointF PhysicsEntity::toWorldVector(QPointF localVector)
{
    if(mBody){
        return mBody->toWorldVector(localVector);
    }else{
        return QPointF();
    }
}

QPointF PhysicsEntity::toLocalPoint(QPointF worlPoint)
{
    if(mBody){
        return mBody->toLocalPoint(worlPoint);
    }else{
        return QPointF();
    }
}

QPointF PhysicsEntity::toLocalVector(QPointF worldVector)
{
    if(mBody){
        return mBody->toLocalVector(worldVector);
    }else{
        return QPointF();
    }
}

QPointF PhysicsEntity::getLinearVelocityFromWorldPoint(QPointF point)
{
    if(mBody){
        return mBody->getLinearVelocityFromWorldPoint(point);
    }else{
        return QPointF();
    }
}

QPointF PhysicsEntity::getLinearVelocityFromLocalPoint(QPointF point)
{
    if(mBody){
        return mBody->getLinearVelocityFromLocalPoint(point);
    }else{
        return QPointF();
    }
}



