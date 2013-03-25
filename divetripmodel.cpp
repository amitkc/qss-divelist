#include "divetripmodel.h"

#include <QtDebug>

/* Item */
DiveItem::DiveItem(int num, QString dt, float dur, float dep, QString loc, DiveItem *p):
    m_number(num), m_dateTime(dt), m_duration(dur), m_depth(dep), m_location(loc), m_parent(p)
{
    if (m_parent)
        m_parent->addChild(this);
}


/* Model */
DiveTripModel::DiveTripModel(const QString &filename, QObject *parent) : QAbstractItemModel(parent), m_Filename(filename)
{
    m_RootItem = new DiveItem;
    qDebug() << "pointer to root item " << m_RootItem;
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

/* Row count of the item in the tree.
 *
 * This gives the row coordinates of any item directly underneath a particular item.
 * It does not give a cumulative count of children and their children, for example.
 *
 * If we don't support dive trips then this must be zero.
 *
*/
int DiveTripModel::rowCount(const QModelIndex &parent) const
{
    /* only allow kids in column 0 */
    if (parent.isValid() && parent.column() > 0){
        return 0;
    }
    DiveItem * item = itemForIndex(parent);
    return item ? item->childCount() : 0;
}



/* Column count of the item in the tree.
 *
 * This is defined by the number of fields in a DiveItem
 *
*/
int DiveTripModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() > 0)
        return 0;

    return COLUMNS;
}

/* Index
 *
 * Unless we allow for Trips to be parents, the parent is always the root.
 *
*/
QModelIndex DiveTripModel::index(int row, int column, const QModelIndex &parent) const
{
//    Q_UNUSED(row)
//    Q_UNUSED(column)
//    Q_UNUSED(parent)

    if (!m_RootItem || row < 0 || column < 0 || column >= COLUMNS
            || ( parent.isValid() && parent.column() != 0) )
        return QModelIndex();

    DiveItem *parentItem = itemForIndex(parent);
    Q_ASSERT(parentItem);
    if ( DiveItem *item = parentItem->childAt(row) )
        createIndex(row, column, item);

    return QModelIndex();

}

/* Parent

  At present the parent is the invisible root with invalid QModelIndex

*/
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


/*! Translate a QModelIndex into an item pointer
 *
 * When we create a short-lived QModelIndex we pass it row, col, a pointer to provide direct
 * access to an element and its methods. Here we retrieve the pointer that was stored in index.
 *
 * This is slightly confusing since in the context of a treemodel we think of the index in terms
 * the rol, column and parent.
 *
*/
DiveItem * DiveTripModel::itemForIndex(const QModelIndex &index) const
{
    if (!index.isValid())
        return m_RootItem;

    DiveItem * item = static_cast<DiveItem*>(index.internalPointer());
    if (item)
        return item;

    return m_RootItem;
}
