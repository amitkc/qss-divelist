#include "divetripmodel.h"

DiveItem::DiveItem(int num, QString dt, float dur, float dep, QString loc, DiveItem *p):
    m_number(num), m_dateTime(dt), m_duration(dur), m_depth(dep), m_location(loc), m_parent(p)
{
    /* nothing else? */
}

DiveTripModel::DiveTripModel(QObject *parent) : QAbstractItemModel(parent)
{
}


Qt::ItemFlags DiveTripModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags diveFlags = QAbstractItemModel::flags(index);
    if(index.isValid()){
        diveFlags |= Qt::ItemIsSelectable|Qt::ItemIsEnabled;
    }
    return diveFlags;
}

QVariant DiveTripModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

QVariant DiveTripModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole){
        if( section == DIVE_NUMBER){
            return tr("Dive number");
        } else if (section == DIVE_DATE_TIME) {
            return tr("Date");
        } else if (section == DIVE_DURATION) {
            return tr("Duration");
        } else if (section == DIVE_DEPTH) {
            return tr("Depth");
        } else if (section == DIVE_LOCATION){
            return tr("Location");
        }
    }
    return QVariant();
}

int DiveTripModel::rowCount(const QModelIndex &parent) const
{
    return 0;
}
