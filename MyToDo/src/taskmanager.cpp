#include "include/taskmanager.h"

TaskManager::TaskManager(QObject *parent)
{
    m_dbManager = new DBManager(this);
    loadTasks();
}

void TaskManager::addTask(const QString &title,const QString &description,const QString &date,bool status) {
    beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));
    qDebug()<<"date"<< date;;
    int id = m_dbManager->insertTask(title, description, date, status);
    Task t(id,title, description,date,status);
    m_tasks.append(t);
    endInsertRows();
}

void TaskManager::removeTask(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    m_dbManager->deleteTask(m_tasks[index].id());
    m_tasks.removeAt(index);
    endRemoveRows();
}

void TaskManager::updateDescription(const QModelIndex &index, const QString &description)
{
    setData(index, description, Roles::Description);
}

void TaskManager::updateStatus(const QModelIndex &index, const bool &status)
{
    setData(index, status, Roles::Status);
}

void TaskManager::updateTitle(const QModelIndex &index, const QString &title)
{
    setData(index, title, Roles::Title);
}

void TaskManager::updateDate(const QModelIndex &index, const QString &date)
{
    setData(index, date, Roles::Date);
}

int TaskManager::rowCount(const QModelIndex &parent) const {
    return m_tasks.count();
}

QSqlQueryModel* TaskManager::getTasks()
{
    return m_dbManager->getTasks();
}

QVariant TaskManager::data(const QModelIndex &index, int role) const {
    Task t = m_tasks.at(index.row());
    switch (role) {
    case Roles::Title:
        return t.title();
    case Roles::Description:
        return t.description();
    case Roles::Date:
        return t.date();
    case Roles::Status:
        return t.status();
    }
    return QVariant();
}

bool TaskManager::setData(const QModelIndex &index, const QVariant &value, int role) {
    qDebug() << "setData " << index.row() << role << value ;
    Task &task  = m_tasks[index.row()];
    qDebug() <<"Task description"<< task.description();
    switch (role) {
    case Roles::Title:
        task.setTitle(value.toString());
        m_dbManager->updateTitle(task.id(),value.toString());
        emit dataChanged(index, index, {role, Title});
        return true;
    case Roles::Description:
        task.setDescription(value.toString());
        m_dbManager->updateDescription(task.id(),value.toString());
        emit dataChanged(index, index, {role, Description});
        return true;
    case Roles::Date:
        task.setDate(value.toString());
        m_dbManager->updateDate(task.id(),value.toString());
        emit dataChanged(index, index, {role, Date});
        return true;
    case Roles::Status:
        task.setStatus(value.toBool());
        m_dbManager->updateStatus(task.id(),value.toBool());
        emit dataChanged(index, index, {role, Status});
        return true;
    }
    return false;
}

void TaskManager::loadTasks()
{
    m_tasks.clear();
    QSqlQueryModel* model = m_dbManager->getTasks();
    int rowCount = model->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        int id = model->record(i).value("id").toInt();
        QString title = model->record(i).value("title").toString();
        QString description = model->record(i).value("description").toString();
        QString date = model->record(i).value("date").toString();
        bool status = model->record(i).value("status").toBool();
        Task task(id,title, description, date, status);
        m_tasks.append(task);
    }
    delete model;
}

QVector<Task> TaskManager::tasks() const
{
    return m_tasks;
}

QHash<int, QByteArray> TaskManager::roleNames() const {
    QHash<int, QByteArray> res;
    res.insert(Roles::Title, "title");
    res.insert(Roles::Description, "description");
    res.insert(Roles::Date, "date");
    res.insert(Roles::Status, "status");
    return res;
}
