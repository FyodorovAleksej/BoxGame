#include "scene.h"
#include <Box2D/Box2D.h>
#include "vector"
#include<windows.h>

qreal abs(qreal x)
{
    if (x >= 0) return x;
    else return -x;
}

Scene::Scene(qreal x,qreal y, qreal width, qreal height, b2World *world)
    : QGraphicsScene(Common::fromB2(x),Common::fromB2(y),Common::fromB2(width),Common::fromB2(height))
{
    qDebug() << "creating scene";
    active = true;
    this->world = world;
    this->shadowableList = new QList<Shadowable*>;
    this->lightableList = new QList<Lightable*>;
    this->pointsList = new QList<QPointF>;
    this->lineList = new QList<QGraphicsItem*>;
    this->bodyes = new QList<b2Body*>;
    this->otherItems = new QList<QGraphicsItem*>;
    this->mutex = new QMutex();
    this->hero = NULL;
}

Scene::~Scene()
{
    qDebug() << "deleting scene";

    if (pointsList != NULL)
    {
        delete pointsList;
        pointsList = NULL;
    }
    if (lineList != NULL)
    {
        foreach (QGraphicsItem* item, *lineList) {
            this->removeItem(item);
            delete item;
        }
        delete lineList;
        lineList = NULL;
    }

    if (hero != NULL)
    {
        delete hero;
        hero = NULL;
    }

    if (shadowableList != NULL)
    {
        delete shadowableList;
        shadowableList = NULL;
    }

    if (lightableList != NULL)
    {
        delete lightableList;
        lightableList = NULL;
    }

    /*if (world != NULL)
    {
        if (world->GetBodyCount() > 0)
        {
            b2Body* node = world->GetBodyList();
            while(node != NULL)
            {
                b2Body* b = node;
                node = node->GetNext();
                world->DestroyBody(b);
            }
        }
        delete world;
        world = NULL;
    }
    */

    if (bodyes != NULL)
    {
        delete bodyes;
        bodyes = NULL;
    }

    if (otherItems != NULL)
    {
        delete otherItems;
        otherItems = NULL;
    }

    //delete world;
}

CircleObject *Scene::getHero()
{
    qDebug() << "getting hero";
    return this->hero;
}
void Scene::setHero(CircleObject *hero)
{
    qDebug() << "setting hero";
    this->hero = hero;
}

void Scene::advance()
{
    qDebug() << "advance before mutex";
    if (world != NULL)
    {
        world->Step(1.00f/60.00,6,2);
    }
    QGraphicsScene::advance();
  //  this->update();
    mutex->lock();
    {
        qDebug() << "advance after mutex";
        if (!active)
        {
            if (bodyes != NULL)
            {
                foreach (b2Body* b, *bodyes) {
                    b->SetActive(true);
                }
            }
        }

        if (active)
        {
            if (bodyes != NULL)
            {
                if (this->bodyes->size() != 0)
                {
                    foreach (b2Body* b, *bodyes) {
                        this->world->DestroyBody(b);
                    }
                    bodyes->clear();
                }
            }

            if (lineList != NULL)
            {
                foreach (QGraphicsItem* line, *lineList) {
                    this->removeItem(line);
                }
                lineList->clear();
            }
            //qDebug() << "size of line" << lineList->size();
            //qDebug() << "size of bodyes" << bodyes->size();
            //qDebug() << "size of shadowable" << shadowableList->size();
            //qDebug() << "size of lighting" << lightableList->size();
            if (lightableList != NULL)
            {
                foreach (Lightable* light, *this->lightableList)
                {
                    if (light->isActive())
                    {
                        foreach (Shadowable *rect, *this->shadowableList)
                        {
                            if (rect->isActive())
                            {
                                if (pointsList != NULL)
                                {
                                    pointsList->append(*(rect->addShadow(light->getLight())));
                                }
                            }
                        }
                        int i = 0;
                        QGraphicsLineItem *lastLine = NULL;

                        if (pointsList != NULL)
                        {
                            foreach (QPointF point, *pointsList) {
                                i++;
                                QGraphicsLineItem *line = this->createLine(light->getLight(), point);
                                if (i % 2 == 0)
                                {
                                    QGraphicsPolygonItem* item = createShadow(line,lastLine);
                                    item->setBrush(QBrush(QColor(123,123,123,75)));
                                    this->addItem(item);
                                    lineList->append(item);
                                }
                                lastLine=line;
                            }
                            pointsList->clear();
                        }
                    }
                }
            }
        }
        mutex->unlock();
    }
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "keyPressEvent";
    switch(event->key())
    {
    case Qt::Key_Up:
    {
        if (!event->isAutoRepeat())
        {
            if (hero != NULL)
            {
                this->hero->upPressed();
            }
        }
        break;
    }
    case Qt::Key_Left:
    {
        if (!event->isAutoRepeat())
        {
            if (hero != NULL)
            {
                this->hero->leftPressed();
            }
        }
        break;
    }
    case Qt::Key_Right:
    {
        if (!event->isAutoRepeat())
        {
            if (hero != NULL)
            {
                this->hero->rightPressed();
            }
        }
        break;
    }
        /*case Qt::Key_Down:
    {
        break;
    }*/
    }

}
void Scene::keyReleaseEvent(QKeyEvent *event)
{
    qDebug() << "keyReleaseEvent";
    switch(event->key())
    {
    case Qt::Key_Up:
    {
        if (!event->isAutoRepeat())
        {
            if (hero != NULL)
            {
                this->hero->upReleased();
            }
        }
        break;
    }
    case Qt::Key_Left:
    {
        if (!event->isAutoRepeat())
        {
            if (hero != NULL)
            {
                this->hero->leftReleased();
            }
        }
        break;
    }
    case Qt::Key_Right:
    {
        if (!event->isAutoRepeat())
        {
            if (hero != NULL)
            {
                this->hero->rightReleased();
            }
        }
        break;
    }
    case Qt::Key_Down:
    {
        if(!event->isAutoRepeat())
        {
            active = !active;
        }
        break;
    }
    case Qt::Key_R:
    {
        if(!event->isAutoRepeat())
        {
            emit (restartSignal());
        }
        break;
    }
    case Qt::Key_Escape:
    {
        if(!event->isAutoRepeat())
        {
            emit (exitSignal());
        }
        break;
    }
    }
}

QList<Shadowable*>* Scene::getShadowList()
{
    qDebug() << "getting shadow list";
    return this->shadowableList;
}
QList<Lightable*>* Scene::getLightList()
{
    qDebug() << "getting lightable list";
    return this->lightableList;
}
QList<b2Body*> Scene::getBodies()
{
    qDebug() << "getting bodies";
    return *this->bodyes;
}

void Scene::addHero(CircleObject *newHero)
{
    qDebug() << "adding hero";
    mutex->lock();
    this->addItem(newHero);
    this->lightableList->append(newHero);
    if (otherItems != NULL)
    {
        this->otherItems->append(newHero);
    }
    mutex->unlock();
}

void Scene::addGround(GroundRect *rect)
{
    qDebug() << "adding ground";
    mutex->lock();
    this->addItem(rect);
    if (shadowableList != NULL)
    {
        this->shadowableList->append(rect);
    }
    if (otherItems != NULL)
    {
        otherItems->append(rect);
    }
    mutex->unlock();
}

QGraphicsLineItem* Scene::createLine(QPointF light, QPointF point)
{
    //qreal x = point.x() - light.x();
    //qreal y = point.y() - light.y();

    qDebug() << "creating line";
    QLineF *line = new QLineF(light,point);
    qreal angle = line->angle();
    //qDebug() << "line angle - " << angle;
    QLineF *result = new QLineF(point.x(), point.y(), point.x() + 1.00f, point.y() + 1.00f);
    result->setLength(1000.00f);
    result->setAngle(angle);

    return new QGraphicsLineItem(*result);
    /*
    qreal tang = abs(y/x);
    if (x >= 0 && y < 0)
    {
        qreal tangScene = abs((this->sceneRect().topRight().y() - light.y())/(this->sceneRect().topRight().x() - light.x()));
        if (tang < tangScene)
        {
            qreal sceneY = -tang * sceneRect().topRight().x() - light.y();
            return new QGraphicsLineItem(point.x(),point.y(),sceneRect().topRight().x(),sceneY);
        }
        else
        {
            qreal sceneX = -(sceneRect().topRight().y()+light.y())/tang;
            return new QGraphicsLineItem(point.x(),point.y(),sceneX,sceneRect().topRight().y());
        }
    }
    if (x < 0 && y < 0)
    {
        qreal tangScene = abs((this->sceneRect().topLeft().y() - light.y())/(this->sceneRect().topLeft().x() - light.x()));
        if (tang < tangScene)
        {
            qreal sceneY = tang * sceneRect().topLeft().x() + light.y();
            return new QGraphicsLineItem(point.x(),point.y(),this->sceneRect().topLeft().x(),sceneY);
        }
        else
        {
            qreal sceneX = (sceneRect().topLeft().y()-light.y())/tang;
            return new QGraphicsLineItem(point.x(),point.y(),sceneX,sceneRect().topLeft().y());
        }
    }
    if (x < 0 && y >= 0)
    {
        qreal tangScene = abs((this->sceneRect().bottomLeft().y() - light.y())/(this->sceneRect().bottomLeft().x() - light.x()));
        if (tang < tangScene)
        {
            qreal sceneY = -tang * sceneRect().bottomLeft().x() - light.y();
            return new QGraphicsLineItem(point.x(),point.y(),sceneRect().bottomLeft().x(),sceneY);
        }
        else
        {
            qreal sceneX = -(sceneRect().bottomLeft().y() + light.y())/tang;
            return new QGraphicsLineItem(point.x(),point.y(),sceneX,sceneRect().bottomLeft().y());
        }
    }
    if (x >= 0 && y >= 0)
    {
        qreal tangScene = abs((this->sceneRect().bottomRight().y() - light.y())/(this->sceneRect().bottomRight().x() - light.x()));
        if (tang < tangScene)
        {
            qreal sceneY = tang * sceneRect().bottomRight().x() + light.y();
            return new QGraphicsLineItem(point.x(),point.y(),sceneRect().bottomRight().x(),sceneY);
        }
        else
        {
            qreal sceneX = (sceneRect().bottomRight().y()-light.y())/tang;
            return new QGraphicsLineItem(point.x(),point.y(),sceneX,sceneRect().bottomRight().y());
        }
}
*/
}
QGraphicsPolygonItem* Scene::createShadow(QGraphicsLineItem* line1, QGraphicsLineItem* line2)
{
    qDebug() << "creating shadow";
    QVector<QPointF> points;
    points.append(line1->line().p1());
    points.append(line1->line().p2());
    points.append(line2->line().p2());
    points.append(line2->line().p1());

    if (active)
    {
        b2Vec2 verticies[4];
        verticies[0].Set(Common::toB2(line1->line().p1().x()), Common::toB2(line1->line().p1().y()));
        verticies[1].Set(Common::toB2(line1->line().p2().x()), Common::toB2(line1->line().p2().y()));
        verticies[2].Set(Common::toB2(line2->line().p1().x()), Common::toB2(line2->line().p1().y()));
        verticies[3].Set(Common::toB2(line2->line().p2().x()), Common::toB2(line2->line().p2().y()));

        b2PolygonShape polygon;
        polygon.Set(verticies, 4);

        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;

        if (world != NULL)
        {
            b2Body* body = this->world->CreateBody(&bodyDef);
            body->CreateFixture(&polygon, 0.0f);

            if (bodyes != NULL)
            {
                this->bodyes->append(body);
            }
            body->SetActive(false);
        }
    }
    return new QGraphicsPolygonItem(QPolygonF(points));
}

void Scene::addLamp(Lamp* light)
{
    qDebug() << "adding lamp";
    this->addItem(light);

    if (lightableList != NULL)
    {
        this->lightableList->append(light);
    }
    otherItems->append(light);
}
void Scene::addGoal(Goal* goal)
{
    qDebug() << "adding goal";
    this->addItem(goal);
    otherItems->append(goal);
}

void Scene::clearShadows()
{
    qDebug() << "clear shadows before mutex";
    mutex->lock();
    this->active = true;
    qDebug() << "clear shadows after mutex";

    if (pointsList != NULL)
    {
        pointsList->clear();
    }

    if (lineList != NULL)
    {
        foreach (QGraphicsItem* item, *lineList)
        {
            this->removeItem(item);
           delete item;
        }
        lineList->clear();
    }

    //delete lineList;
    //delete hero;

    //delete shadowableList;
    if (shadowableList != NULL)
    {
        shadowableList->clear();
    }

    //delete lightableList;

    if (lightableList != NULL)
    {
        lightableList->clear();
    }

    //this->clear();
    if (world != NULL)
    {
        if (world->GetBodyCount() > 0)
        {
            b2Body* node = world->GetBodyList();
            while(node != NULL)
            {
                b2Body* b = node;
                node = node->GetNext();
                world->DestroyBody(b);
            }
        }
    }
    //delete bodyes;

    if (bodyes != NULL)
    {
        bodyes->clear();
    }

    //delete otherBodyes;

    if (otherItems != NULL)
    {
        foreach (QGraphicsItem* item, *otherItems) {
           this->removeItem(item);
        }
        otherItems->clear();
    }

    if (hero != NULL)
    {
        removeItem(hero);
        delete hero;
        hero = NULL;
    }

    qDebug() << "2d items - " << world->GetBodyCount();

   // this->clear();
    //this->update();

    /*pointsList= new QList<QPointF>;
    lineList= new QList<QGraphicsItem*>;
    shadowableList= new QList<Shadowable*>;
    lightableList = new QList<Lightable*>;
    bodyes = new QList<b2Body*>;
    otherBodyes = new QList<b2Body*>;
    */

    mutex->unlock();
}
