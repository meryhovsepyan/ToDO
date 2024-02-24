#include "include/filter_manager.h"
#include "include/taskmanager.h"

FilteredModel::FilteredModel(QObject *parent)
    : QSortFilterProxyModel(parent) {
}

void FilteredModel::setSourceModelQML(QAbstractItemModel *sourceModel) {
    qDebug() << Q_FUNC_INFO;
    this->setSourceModel(sourceModel);
}

int FilteredModel::mapIndexFromSource(int row) {
    QModelIndex idx = this->index(row, 0);
    return mapToSource(idx).row();
}

void FilteredModel::setFilterTitle(const QString &titleText) {
    entered_data = titleText;
    this->setFilterRole(TaskManager::Title);
    invalidateFilter();
}

void FilteredModel::setFilterDescription(const QString &descText) {
    entered_data = descText;
    this->setFilterRole(TaskManager::Description);
    invalidateFilter();
}

void FilteredModel::setFilterStatus(const bool &status) {
    entered_data = status;
    this->setFilterRole(TaskManager::Status);
    invalidateFilter();
}

void FilteredModel::setFilterDate(const QString &date) {
    entered_data = date;
    this->setFilterRole(TaskManager::Date);
    invalidateFilter();
}

bool FilteredModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const {
    QModelIndex idx = sourceModel() ->index(source_row, 0, source_parent);
    auto role = filterRole();
    QVariant data = sourceModel()->data(idx, role);
    switch (role) {
    case TaskManager::Title:
    {
        QString title = data.toString();
        return title.startsWith(entered_data.toString());
        break;
    }
    case TaskManager::Description:
    {
        QString desc = data.toString();
        return desc.startsWith(entered_data.toString());
        break;
    }
    case TaskManager::Status:
    {
        bool status = data.toBool();
        return status==entered_data.toBool();
        break;
    }
    case TaskManager::Date:
    {
        QStringList dateList = entered_data.toString().split(" ");
        QDate startDate = QDate::fromString(dateList[0], "dd-MM-yyyy");
        QDate endDate = QDate::fromString(dateList[1], "dd-MM-yyyy");
        QDate myDate = QDate::fromString(data.toString(), "dd-MM-yyyy");
        return (myDate >= startDate && myDate <= endDate);
    }
    default:
        return false;
    }
}

