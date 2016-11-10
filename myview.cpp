#include "myview.h"

MyView::MyView(QWidget *parent):QGraphicsView(parent)
{
    setRubberBandSelectionMode(Qt::ContainsItemShape);
    }

void MyView::setMyDragMode(bool ok)
{
    if(ok)
        setDragMode(QGraphicsView::ScrollHandDrag);
    else setDragMode(QGraphicsView::NoDrag);
}

void MyView::setMySelectMode(bool ok)
{
    if(ok)
        setDragMode(QGraphicsView::RubberBandDrag);
    else setDragMode(QGraphicsView::NoDrag);
}

void MyView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}

void MyView::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
        scale(1.2, 1.2);
    else scale(1/1.2,1/1.2);
}
