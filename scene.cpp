#include "scene.h"

qreal abs(qreal x)
{
    if (x >= 0) return x;
    else return -x;
}

Scene::Scene(qreal x,qreal y, qreal width, qreal height, b2World *world)
    : QGraphicsScene(Common::fromB2(x),Common::fromB2(y),Common::fromB2(width),Common::fromB2(height))
{
    this->world = world;
    this->shadowableList = new QList<Shadowable*>;
    this->lightableList = new QList<Lightable*>;
    this->pointsList = new QList<QPointF>;
    this->lineList = new QList<QGraphicsItem*>;
}

CircleObject *Scene::getHero()
{
    return this->hero;
}

void Scene::setHero(CircleObject *hero)
{
    this->hero = hero;
}

void Scene::advance()
{
    world->Step(1.00f/60.00,6,2);
    QGraphicsScene::advance();
    if (active)
    {
        foreach (Lightable* light, *this->lightableList)
        {
            foreach (Shadowable *rect, *this->shadowableList)
            {
                pointsList->append(*(rect->addShadow(light->getLight())));
            }

            foreach (QGraphicsItem* line, *lineList) {
                this->removeItem(line);
            }

            lineList->clear();
            int i = 0;
            QGraphicsLineItem *lastLine = NULL;
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

void Scene::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Up:
    {
        if (!event->isAutoRepeat())
        {
            this->hero->upPressed();
        }
        break;
    }
    case Qt::Key_Left:
    {
        if (!event->isAutoRepeat())
        {
            this->hero->leftPressed();
        }
        break;
    }
    case Qt::Key_Right:
    {
        if (!event->isAutoRepeat())
        {
            this->hero->rightPressed();
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
    switch(event->key())
    {
    case Qt::Key_Up:
    {
        if (!event->isAutoRepeat())
        {
            this->hero->upReleased();
            GroundRect *rect = new GroundRect(world,QSizeF(4, 0.3), QPointF(2, 1), 15);
            QList<QPointF> *points = rect->getPoints();
            for (int  i = 0; i < 4; i++)
            {
                qDebug() << "adding";
                this->addItem(new QGraphicsEllipseItem(points->at(i).x()-6.00f, points->at(i).y() - 6.00f, 12,12));
            }
        }
        break;
    }
    case Qt::Key_Left:
    {
        if (!event->isAutoRepeat())
        {
            this->hero->leftReleased();
        }
        break;
    }
    case Qt::Key_Right:
    {
        if (!event->isAutoRepeat())
        {
            this->hero->rightReleased();
        }
        break;
    }
    case Qt::Key_Down:
    {
        active = !active;
        break;
    }
    }
}

QList<Shadowable*>* Scene::getShadowList()
{
    return this->shadowableList;
}

QList<Lightable*>* Scene::getLightList()
{
    return this->lightableList;
}

void Scene::addHero(CircleObject *hero)
{
    this->hero = hero;
    this->addItem(hero);
    this->lightableList->append(hero);
}
void Scene::addGround(GroundRect *rect)
{
    this->addItem(rect);
    this->shadowableList->append(rect);
}

QGraphicsLineItem* Scene::createLine(QPointF light, QPointF point)
{
    qreal x = point.x() - light.x();
    qreal y = point.y() - light.y();

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
}

QGraphicsPolygonItem* Scene::createShadow(QGraphicsLineItem* line1, QGraphicsLineItem* line2)
{
    QVector<QPointF> points;
    points.append(line1->line().p1());
    points.append(line1->line().p2());
    points.append(line2->line().p2());
    points.append(line2->line().p1());
    return new QGraphicsPolygonItem(QPolygonF(points));
}
