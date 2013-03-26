#include "divetripmodel.h"


DiveItem::DiveItem(int num, QString dt, float dur, float dep, QString loc, DiveItem *p):
    m_number(num), m_dateTime(dt), m_duration(dur), m_depth(dep), m_location(loc), m_parent(p)
{
    if (m_parent)
        m_parent->addChild(this);
}


DiveTripModel::DiveTripModel(const QString &filename, QObject *parent) : QAbstractItemModel(parent), m_Filename(filename)
{
    m_RootItem = new DiveItem;
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
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    DiveItem *item = static_cast<DiveItem*>(index.internalPointer());

    QVariant retVal;
    switch( index.column())
    {
    case DIVE_NUMBER:
        retVal = QVariant(item->diveNumber());
        break;
    case DIVE_DATE_TIME:
        retVal = QVariant(item->dateTime());
        break;
    case DIVE_DURATION:
        retVal = QVariant(item->duration());
        break;
    case DIVE_DEPTH:
        retVal = QVariant(item->depth());
        break;
    case DIVE_LOCATION:
        retVal = QVariant(item->location());
        break;
    default:
        return QVariant();
    };
    return retVal;
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
    /* only allow kids in column 0 */
    if (parent.isValid() && parent.column() > 0){
        return 0;
    }
    DiveItem * item = itemForIndex(parent);
    return item ? item->childCount() : 0;
}



int DiveTripModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() && parent.column() != 0 ? 0 : COLUMNS;

}


QModelIndex DiveTripModel::index(int row, int column, const QModelIndex &parent) const
{

    if (!m_RootItem || row < 0 || column < 0 || column >= COLUMNS
            || ( parent.isValid() && parent.column() != 0) )
        return QModelIndex();

    DiveItem *parentItem = itemForIndex(parent);
    Q_ASSERT(parentItem);
    if ( DiveItem *item = parentItem->childAt(row) ){
        return createIndex(row, column, item);
    }
    return QModelIndex();

}


QModelIndex DiveTripModel::parent(const QModelIndex &childIndex) const
{
    if (!childIndex.isValid())
        return QModelIndex();

    DiveItem *child = static_cast<DiveItem*>(childIndex.internalPointer());
    DiveItem *parent = child->parent();

    if (parent == m_RootItem)
        return QModelIndex();

    return createIndex(parent->rowOfChild(child), 0, parent);
}


DiveItem * DiveTripModel::itemForIndex(const QModelIndex &index) const
{
    if (index.isValid()) {
        DiveItem * item = static_cast<DiveItem*>(index.internalPointer());
        return item;
    }
    return m_RootItem;
}
