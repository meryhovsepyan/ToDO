#ifndef FILTERMANAGER_H
#define FILTERMANAGER_H

#include <QObject>
#include <QSortFilterProxyModel>

class FilteredModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit FilteredModel(QObject *parent = nullptr);

signals:

public:
    Q_INVOKABLE void setSourceModelQML(QAbstractItemModel *sourceModel);

    Q_INVOKABLE int mapIndexFromSource(int row);

    Q_INVOKABLE void setFilterTitle(const QString & titleText);
    Q_INVOKABLE void setFilterDescription(const QString & descText);
    Q_INVOKABLE void setFilterStatus(const bool & status);
    Q_INVOKABLE void setFilterDate(const QString & date);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

private:
    QVariant entered_data;
};

#endif // FILTERMANAGER_H
