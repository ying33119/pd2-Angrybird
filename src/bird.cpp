#include "bird.h"

Bird::Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(radius*2,radius*2);

    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2CircleShape bodyshape;
    bodyshape.m_radius = radius;

    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = BIRD_DENSITY;
    fixturedef.friction = BIRD_FRICTION;
    fixturedef.restitution = BIRD_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}

void Bird::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}
double Bird::getVelX(){
    b2Vec2 vel = g_body->GetLinearVelocity();
    return vel.x;
}
double Bird::getVelY(){
    b2Vec2 vel = g_body->GetLinearVelocity();
    return vel.y;
}

void pig::effect(){}
void birdR::effect(){}
void birdX::effect(){
    setLinearVelocity(b2Vec2(0,this->getVelY()-30));
}
void birdY::effect(){
    setLinearVelocity(b2Vec2(this->getVelX()*5,this->getVelY()*8));
}
void birdB::effect(){
    g_pixmap.setPixmap(QPixmap(":/image/birdB.png").scaled(200,200));
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(Radius*11,Radius*11);
    g_body->SetLinearVelocity(b2Vec2(g_body->GetLinearVelocity().x*2,g_body->GetLinearVelocity().y*2));
}

