#ifndef BIRD_H
#define BIRD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define BIRD_DENSITY 10.0f*2
#define BIRD_FRICTION 0.2f
#define BIRD_RESTITUTION 0.5f/2.0

class Bird : public GameItem
{
public:
    Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
    virtual void effect()=0;
    double getVelX();
    double getVelY();
    bool shot = false;
    bool advanced = false;
};
class pig : public Bird{
public:
    pig(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):
        Bird(x,y,radius,timer,pixmap,world,scene){}
    virtual void effect();
};
class birdR: public Bird{
public:
    birdR(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):
        Bird(x,y,radius,timer,pixmap,world,scene){}
    virtual void effect();
};
class birdX: public Bird{
public:
    birdX(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):
        Bird(x,y,radius,timer,pixmap,world,scene){}
    virtual void effect();
};
class birdY: public Bird{
public:
    birdY(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):
        Bird(x,y,radius,timer,pixmap,world,scene){}
    virtual void effect();
};
class birdB: public Bird{
public:
    birdB(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):
        Bird(x,y,radius,timer,pixmap,world,scene){
        radius = radius;
    }
    virtual void effect();
private:
    float radius;
};
#endif // BIRD_H
