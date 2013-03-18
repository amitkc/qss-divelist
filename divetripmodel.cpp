#include "divetripmodel.h"

/* Item */
DiveItem::DiveItem(int num, QString dt, float dur, float dep, QString loc, DiveItem *p):
    m_number(num), m_dateTime(dt), m_duration(dur), m_depth(dep), m_location(loc), m_parent(p)
{
    /* nothing else? */
}


/* Model */
DiveTripModel::DiveTripModel(const QString &filename, QObject *parent) : QAbstractItemModel(parent), m_Filename(filename)
{
    m_RootItem = 0;
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
    Q_UNUSED(parent)

    return 0;
}



/* Column count of the item in the tree.
 *
 * This is defined by the number of fields in a DiveItem
 *
*/
int DiveTripModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return COLUMNS;
}

/* Index
 *
 * Unless we allow for Trips to be parents, the parent is always the root.
 *
*/
QModelIndex DiveTripModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(row)
    Q_UNUSED(column)
    Q_UNUSED(parent)

    if (!m_RootItem || row < 0 || column < 0 || column >= COLUMNS
            || ( parent.isValid() && parent.column() != 0) )
        return QModelIndex();

    return QModelIndex();

}

/* Parent

  At present the parent is the invisible root with invalid QModelIndex

*/
QModelIndex DiveTripModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}


/*! Translate a QModelIndex into an item pointer
 *
 * When we create a short-lived QMI we pass it row, col, parent and can add a pointer to provide
 * direct access to an element and its methods. Here we retrieve the pointer that was stored in
 * the QMI.
*/
DiveItem * DiveTripModel::itemForIndex(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    DiveItem * item = static_cast<DiveItem*> index.internalPointer();
    if (item)
        return item;

    return QModelIndex();
}
