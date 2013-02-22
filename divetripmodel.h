#ifndef DIVETRIPMODEL_H
#define DIVETRIPMODEL_H

#include <QAbstractItemModel>

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

private:

    int m_number;
    QString m_dateTime;
    float m_duration;
    float m_depth;
    QString m_location;

    DiveItem *m_parent;
    QList <DiveItem*> m_children;

};

enum Column {DIVE_NUMBER, DIVE_DATE_TIME, DIVE_DURATION, DIVE_DEPTH, DIVE_LOCATION};

class DiveTripModel : public QAbstractItemModel
{
public:
    DiveTripModel(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    int rowCount(const QModelIndex &parent) const;
};

#endif // DIVETRIPMODEL_H
