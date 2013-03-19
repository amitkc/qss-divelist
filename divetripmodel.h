#ifndef DIVETRIPMODEL_H
#define DIVETRIPMODEL_H

#include <QAbstractItemModel>

/*! A DiveItem for use with a DiveTripModel
 *
 * A simple class which wraps basic stats for a dive (e.g. duration, depth) and
 * tidies up after it's children. This is done manually as we don't inherit from
 * QObject.
 *
 * In order to manage the parent-child hierarchy and to provide an adequate set of
 * methods for the model to use we have quite a few methods operating on the list of
 * children the parents hold.
 *
 * \todo Add to parent list when creating an item
 * \todo Consider adding a takeChildItem method (p158) - possibly not required if not doing drag, drop, delete?
 * \todo Consider addition of default constructor to enable container use outside of model.
 * \todo Consider stream operators
 *
 * void addChild(DiveItem *) is called on the parent of newly created items. It adds the newly created item to
 * the child list of the parent. The parent of the newly created item is set to be the item itself.
*/
class DiveItem
{
public:
    explicit DiveItem(int num, QString dt, float, float, QString loc, DiveItem *parent = 0);
    ~DiveItem() { qDeleteAll(m_children); }

    int diveNumber() const {return m_number;}
    QString dateTime() const {return m_dateTime;}
    float duration() const {return m_duration;}
    float depth() const {return m_depth;}
    QString location() const {return m_location;}

    DiveItem *parent() const {return m_parent;}
    DiveItem *childAt(int row) const {return m_children.value(row);}
    int rowOfChild(DiveItem *child) const {return m_children.indexOf(child);}
    int childCount() const {return m_children.count();}
    bool hasChildren() const {return !m_children.isEmpty();}
    QList<DiveItem *> children() const {return m_children;}
    void addChild(DiveItem*item) {item->m_parent = this; m_children << item;} /* parent = self */


private:

    int m_number;
    QString m_dateTime;
    float m_duration;
    float m_depth;
    QString m_location;

    DiveItem *m_parent;
    QList <DiveItem*> m_children;

};

enum Column {DIVE_NUMBER, DIVE_DATE_TIME, DIVE_DURATION, DIVE_DEPTH, DIVE_LOCATION, COLUMNS};

/*! An AbstractItemModel for recording dive trip information such as a list of dives.
 *
 * \todo Capture logic behind parent method and possibly others.
 *
*/
class DiveTripModel : public QAbstractItemModel
{
public:

    DiveTripModel(const QString &filename, QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    int rowCount(const QModelIndex &parent) const;

    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex index(int row, int column,
                              const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &child) const;

    DiveItem * itemForIndex(const QModelIndex &) const;

private:

    DiveItem * m_RootItem;
    QString m_Filename;

};

#endif // DIVETRIPMODEL_H
