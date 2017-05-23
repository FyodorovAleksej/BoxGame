#include "circleobject.h"

CircleObject::CircleObject(QObject *parent) : QObject(parent)
{

}

CircleObject::CircleObject(b2World *world, qreal radius, QPointF initPos)
{
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
    fixture->SetRestitution(0.1);
}
CircleObject::~CircleObject()
{
    body->GetWorld()->DestroyBody(body);
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
    this->leftTimer = new QTimer(this);
    connect(leftTimer,SIGNAL(timeout()),this,SLOT(leftForce()));
    leftTimer->start(10);
}

void CircleObject::rightPressed()
{
    this->rightTimer = new QTimer(this);
    this->rightForceCustom = 0;
    connect(rightTimer, SIGNAL(timeout()),this, SLOT (rightForce()));
    rightTimer->start(10);
    //this->body->ApplyForceToCenter(b2Vec2(1.00f, 0.00f),true);
}



void CircleObject::upReleased()
{
    //this->body->ApplyForceToCenter(b2Vec2(0.00f, 0.00f),true);
}

void CircleObject::leftReleased()
{
    if (leftTimer != NULL)
    {
        leftTimer->stop();
    }
    //this->body->ApplyForceToCenter(b2Vec2(0.00f, 0.00f),true);
}

void CircleObject::rightReleased()
{
    if (rightTimer != NULL)
    {
        rightTimer->stop();
    }
    //this->body->ApplyForceToCenter(b2Vec2(0.00f, 0.00f),true);
}



void CircleObject::leftForce()
{
    this->body->ApplyForceToCenter(b2Vec2(-0.30f, 0.00f),true);
    // this->body->ApplyLinearImpulseToCenter(b2Vec2(-1.00f, 0.00f),true);
}
void CircleObject::rightForce()
{
    this->body->ApplyForceToCenter(b2Vec2(0.30f, 0.00f),true);
    //this->body->ApplyLinearImpulseToCenter(b2Vec2(1.00f, 0.00f),true);
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
        }
    }
}

QPointF CircleObject::getLight()
{
    return this->pos();
}
