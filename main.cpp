#include <QtGui/QApplication>
#include "divelistview.h"
#include "divetripmodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString file = QString("testfile.txt");
    DiveTripModel *model = new DiveTripModel(file, qApp);
    DiveListView *view = new DiveListView();
    view->setModel(model);

    view->show();

    return a.exec();
}
