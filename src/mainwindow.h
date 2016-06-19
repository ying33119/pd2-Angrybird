#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>

#include "gameitem.h"
#include "land.h"
#include "bird.h"
#include "block.h"
#include "button.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void keyPressEvent(QKeyEvent* event);
    void closeEvent(QCloseEvent *);
    void start();

signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void restart();
    void quit();
    void tick();
    void createbird();
    // For debug slot
    void QUITSLOT();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QList<GameItem *> birdList;
    QTimer timer;
    Bird *bird;
    bool waited = false;
    bool move = false;

    int birdnum=0;
};

#endif // MAINWINDOW_H
