#include "circleobject.h"
#include<QDebug>
CircleObject::CircleObject(QObject *parent) : QObject(parent)
{

}
CircleObject::CircleObject(b2World *world, qreal radius, QPointF initPos)
{
    jump = true;
    action = false;
    setRect(-Common::fromB2(radius),-Common::fromB2(radius),Common::fromB2(2*radius),Common::fromB2(2*radius));
    setBrush(QBrush(Qt::green));
    setPos(Common::fromB2(initPos.x()),Common::fromB2(initPos.y()));

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(initPos.x(),initPos.y());
    bodyDef.linearDamping = 0.2;

    this->body = world->CreateBody(&bodyDef);
    b2CircleShape shape;
    shape.m_radius = radius;

    b2Fixture *fixture = body->CreateFixture(&shape,1.0f);
    fixture->SetRestitution(0.2);

    this->goals = new QList<Goal*>;
    this->leftTimer = new QTimer(this);
    this->rightTimer = new QTimer(this);

    connect(leftTimer,SIGNAL(timeout()),this,SLOT(leftForce()));
    connect(rightTimer, SIGNAL(timeout()),this, SLOT (rightForce()));
}
CircleObject::~CircleObject()
{
    //body->GetWorld()->DestroyBody(body);
    if (leftTimer != NULL)
    {
        //leftTimer->stop();
        //delete this->leftTimer;
        leftTimer = NULL;
    }
    if (rightTimer != NULL)
    {
        //rightTimer->stop();
        //delete this->rightTimer;
        rightTimer = NULL;
    }
    if (goals != NULL)
    {
        this->goals->clear();
        delete goals;
        goals = NULL;
    }

}

void CircleObject::upPressed()
{
    if (this->jump)
    {
        this->body->ApplyLinearImpulseToCenter(b2Vec2(0.00f, -1.00f),true);
        this->jump = false;
    }
}
void CircleObject::leftPressed()
{
    leftTimer->start(10);
}
void CircleObject::rightPressed()
{
    rightTimer->start(10);
}

void CircleObject::upReleased()
{

}
void CircleObject::leftReleased()
{
    if (leftTimer != NULL)
    {
        leftTimer->stop();
    }
}
void CircleObject::rightReleased()
{
    if (rightTimer != NULL)
    {
        rightTimer->stop();
    }
}

void CircleObject::leftForce()
{
        this->body->ApplyForceToCenter(b2Vec2(-0.5f, 0.00f), false);
}
void CircleObject::rightForce()
{
        this->body->ApplyForceToCenter(b2Vec2(0.5f, 0.00f), false);
}

void CircleObject::advance(int phase)
{
    if (phase)
    {
        setPos(Common::fromB2(body->GetPosition().x), Common::fromB2(body->GetPosition().y));

        QList<QGraphicsItem *> foundItemsUnder = scene()->items(QPolygonF()
                                                                << mapToScene(1,25)
                                                                << mapToScene(-1,25));
        foreach (QGraphicsItem *item, foundItemsUnder) {
            if (item == this)
                continue;
            jump = true;
            action = false;
        }        

        QList<QGraphicsItem*> foundInCenter = scene()->items(QPolygonF()<<mapToScene(25,25)<<mapToScene(-25,25)<<mapToScene(-25,-25)<<mapToScene(25,-25));
        foreach (QGraphicsItem *item, foundInCenter)
        {
            if (item == this)
                continue;
            if (goals != NULL && goals->size() > 0)
            foreach (Goal* goal, *goals)
            {
                if (goal == item)
                {
                    if (!action)
                    {
                        goal->releaseAction();
                    }
                    action = true;
                }
            }
        }
    }
}

QPointF CircleObject::getLight()
{
    return this->pos();
}
void CircleObject::addGoal(Goal* item)
{
    this->goals->append(item);
}
bool CircleObject::isActive()
{
    return true;
}
b2Body* CircleObject::getBody()
{
    return body;
}
