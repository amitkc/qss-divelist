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

    /* Populate list with random test dives */
    DiveItem * root = model->itemForIndex(QModelIndex());
    if (root){
        d1 = new DiveItem(1,QString("01/03/13"),14.2, 29.0,QString("Wraysbury"),root);
        d2 = new DiveItem(2,QString("09/08/12"),22.7, 32.5,QString("Portland Harbour"),root);
        d3 = new DiveItem(3,QString("01/10/12"),28.3, 16.7,QString("English Channel"),root);

    }

    DiveListView *view = new DiveListView();
    view->setModel(model);
    view->setCurrentIndex(QModelIndex());
    view->setWindowTitle(QObject::tr("Qt Subsurface Dive Trip TreeView"));
    view->resize(600,400);
    view->move(550,350);
    view->show();

    return a.exec();
}
