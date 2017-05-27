#include "circleobject.h"
#include<QDebug>
/**
 * @brief CircleObject::CircleObject - basic Constructor of QObject
 * @param parent - parent of this QObject
 */
CircleObject::CircleObject(QObject *parent) : QObject(parent)
{
}

/**
 * @brief CircleObject::CircleObject - normal constructor of the protagonist
 * @param world - 2dBox physic world
 * @param radius - radius of the Circle (protagonist)
 * @param initPos - position of this Circle (in 2dBox coordinates)
 */
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

    this->interacts = new QList<Interactavable*>;
    this->leftTimer = new QTimer(this);
    this->rightTimer = new QTimer(this);

    connect(leftTimer,SIGNAL(timeout()),this,SLOT(leftForce()));
    connect(rightTimer, SIGNAL(timeout()),this, SLOT (rightForce()));
}

/**
 * @brief CircleObject::~CircleObject - deleting this Hero
 */
CircleObject::~CircleObject()
{
    //body->GetWorld()->DestroyBody(body);
    if (leftTimer != NULL)
    {
        leftTimer = NULL;
    }

    if (rightTimer != NULL)
    {
        rightTimer = NULL;
    }

    if (interacts != NULL)
    {
        this->interacts->clear();
        delete interacts;
        interacts = NULL;
    }
}


/**
 * @brief CircleObject::upPressed - actions, that performed when UP was pressed
 */
void CircleObject::upPressed()
{
    if (this->jump)
    {
        this->body->ApplyLinearImpulseToCenter(b2Vec2(0.00f, -1.00f),true);
        this->jump = false;
    }
}

/**
 * @brief CircleObject::leftPressed - actions, that performed when LEFT was pressed
 * this start the QTimer, for force hero, while LEFT was pressed
 */
void CircleObject::leftPressed()
{
    leftTimer->start(10);
}

/**
 * @brief CircleObject::rightPressed - actions, that performed when RIGHT was pressed
 * this start the QTimer, for force hero, while RIGHT was pressed
 */
void CircleObject::rightPressed()
{
    rightTimer->start(10);
}


/**
 * @brief CircleObject::upReleased - actions, that performed when UP was released
 */
void CircleObject::upReleased()
{
}

/**
 * @brief CircleObject::leftReleased - actions, that performed when LEFT was released
 * stop the QTimer
 */
void CircleObject::leftReleased()
{
    if (leftTimer != NULL)
    {
        leftTimer->stop();
    }
}

/**
 * @brief CircleObject::rightReleased - actions, that performed when RIGHT was relesed
 */
void CircleObject::rightReleased()
{
    if (rightTimer != NULL)
    {
        rightTimer->stop();
    }
}


/**
 * @brief CircleObject::leftForce - actions, for force hero in LEFT
 */
void CircleObject::leftForce()
{
        this->body->ApplyForceToCenter(b2Vec2(-0.5f, 0.00f), false);
}
/**
 * @brief CircleObject::rightForce - actions, for force hero in RIGHT
 */
void CircleObject::rightForce()
{
        this->body->ApplyForceToCenter(b2Vec2(0.5f, 0.00f), false);
}


/**
 * @brief CircleObject::advance - refresh this object (used by QGraphicsScene::advance)
 * @param phase - the phase of refreshing (0 - preparing; 1 - execution)
 */
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
            if (interacts != NULL && interacts->size() > 0)
            foreach (Interactavable* interact, *interacts)
            {
                if (interact == item)
                {
                    if (!action)
                    {
                        interact->releaseAction();
                    }
                    action = true;
                }
            }
        }
    }
}

/**
 * @brief CircleObject::getLight - getting position of this light
 * @return
 */
QPointF CircleObject::getLight()
{
    return this->pos();
}

/**
 * @brief CircleObject::addGoal - adding interactive Object for checking interaction
 * @param item
 */
void CircleObject::addInteract(Interactavable* item)
{
    this->interacts->append(item);
}

/**
 * @brief CircleObject::isActive - this object is always lighting
 * @return always true
 */
bool CircleObject::isActive()
{
    return true;
}

/**
 * @brief CircleObject::getBody - getting physic 2dBox body
 * @return
 */
b2Body* CircleObject::getBody()
{
    return body;
}
