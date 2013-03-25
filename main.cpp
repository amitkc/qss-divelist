#include <QApplication>
#include "divelistview.h"
#include "divetripmodel.h"
#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString file = QString("testfile.txt");
    DiveTripModel *model = new DiveTripModel(file, qApp);
    DiveItem* d1;
    DiveItem* d2;
    DiveItem* d3;

    /* Populate list with test dives starting with root*/
    DiveItem * root = model->itemForIndex(QModelIndex());
    if (root){
        qDebug() << "root is not null so adding children";
//        DiveItem* d1 = new DiveItem(1,QString("01/03/13"),34.2, 49.0,QString("Wraysbury"),root);
//        DiveItem* d2 = new DiveItem(2,QString("01/03/13"),24.7, 32.5,QString("Wraysbury"),root);
//        DiveItem* d3 = new DiveItem(3,QString("01/03/13"),10.3, 42.7,QString("Wraysbury"),root);
        d1 = new DiveItem(1,QString("01/03/13"),34.2, 49.0,QString("Wraysbury"),root);
        d2 = new DiveItem(2,QString("01/03/13"),24.7, 32.5,QString("Wraysbury"),root);
        d3 = new DiveItem(3,QString("01/03/13"),10.3, 42.7,QString("Wraysbury"),root);

        qDebug() << d1->diveNumber() << " " << d1->dateTime() << " "<< d1->depth() << " "<< d1->duration() << " " << d1->location();
        qDebug() << d2->diveNumber() << " " << d2->dateTime() << " "<< d2->depth() << " "<< d2->duration() << " " << d2->location();
        qDebug() << d3->diveNumber() << " " << d3->dateTime() << " "<< d3->depth() << " "<< d3->duration() << " " << d3->location();

        //model->reset();
    }

    DiveListView *view = new DiveListView();
    view->setModel(model);
    view->scrollTo(QModelIndex());
    view->setWindowTitle("Qt Subsurface Dive Trip TreeView");
    view->resize(600,400);
    view->move(550,350);
    view->show();

    return a.exec();
}
