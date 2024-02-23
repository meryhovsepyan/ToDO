#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QObject>
#include <QAbstractListModel>
#include <include/task.h>
#include "db_manager.h"

class TaskManager : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TaskManager(QObject *parent = nullptr);

    Q_INVOKABLE void addTask(const QString &title,const QString &decription,const QString &date,bool status);
    Q_INVOKABLE void removeTask(int index);

    Q_INVOKABLE void updateDescription(const QModelIndex &index, const QString &description);
    Q_INVOKABLE void updateTitle(const QModelIndex &index, const QString &title);
    Q_INVOKABLE void updateDate(const QModelIndex &index, const QString &date);
    Q_INVOKABLE void updateStatus(const QModelIndex &index, const bool &status);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    QVector<Task> tasks() const;
    QSqlQueryModel* getTasks();
    QHash<int, QByteArray> roleNames() const;

    enum Roles {
        Title = Qt::UserRole + 1,
        Description,
        Date,
        Status
    };

signals:
    void tasksChanged();

private:
    QVector<Task> m_tasks;
    DBManager* m_dbManager;
    void loadTasks();

};

#endif // TASKMANAGER_H
