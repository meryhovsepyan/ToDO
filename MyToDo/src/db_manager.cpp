#include "include/db_manager.h"
#include <QCoreApplication>


DBManager::DBManager(QObject *parent)
    : QObject{parent}
{
    init();
    createTable();
}

DBManager::~DBManager()
{
    m_db.close();
}

void DBManager::init()
{
    QString dbFileName = "tasks.db";
    QString dbFilePath = QDir(QCoreApplication::applicationDirPath()).filePath(dbFileName);

    if (m_db.isOpen()) {
        m_db.close();
        QSqlDatabase::removeDatabase(m_db.connectionName());
    }

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbFilePath);

    if (!m_db.open()) {
        qDebug() << "Error: " << m_db.lastError().text();
    }
}

void DBManager::createTable()
{
    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS tasks ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "title TEXT,"
                  "description TEXT,"
                  "date TEXT,"
                  "status BOOLEAN"
                  ");");
    if (!query.exec()) {
        qDebug() << "Errorbb: " << query.lastError().text();
    }
}

int DBManager::insertTask(const QString &title, const QString &description, const QString &date, bool status)
{
    QSqlQuery query;
    query.prepare("INSERT INTO tasks (title, description, date, status) "
                  "VALUES (:title, :description, :date, :status)");
    query.bindValue(":title", title);
    query.bindValue(":description", description);
    query.bindValue(":date", date);
    query.bindValue(":status", status);
    qDebug() << "insert: " << title<< " "<<description<<
        " "<<date << " "<< status<<" ";
    if (!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return -1;
    }
    return query.lastInsertId().toInt();
}

bool DBManager::deleteTask(int taskId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM tasks WHERE id = :id");
    query.bindValue(":id", taskId);
    qDebug() << "delete id: " << taskId;

    return query.exec();
}

bool DBManager::updateTitle(int taskId, const QString &title)
{
    QSqlQuery query;
    query.prepare("UPDATE tasks SET title = :title WHERE id = :id");
    query.bindValue(":title", title);
    query.bindValue(":id", taskId);
    qDebug() << "update id: " << taskId <<"title "<< title;

    return query.exec();
}

bool DBManager::updateDate(int taskId, const QString &date)
{
    QSqlQuery query;
    query.prepare("UPDATE tasks SET date = :date WHERE id = :id");
    query.bindValue(":date", date);
    query.bindValue(":id", taskId);
    qDebug() << "update id: " << taskId <<"date "<< date;
    return query.exec();
}

bool DBManager::updateStatus(int taskId, bool status)
{
    QSqlQuery query;
    query.prepare("UPDATE tasks SET status = :status WHERE id = :id");
    query.bindValue(":status", status);
    query.bindValue(":id", taskId);
    qDebug() << "update id: " << taskId<<"status "<< status;
    return query.exec();
}

bool DBManager::updateDescription(int taskId, const QString &description)
{   QSqlQuery query;
    query.prepare("UPDATE tasks SET description = :description WHERE id = :id");
    query.bindValue(":description", description);
    query.bindValue(":id", taskId);
    qDebug() << "update id: " << taskId <<"desc "<< description;
    return query.exec();
}

QSqlQueryModel* DBManager::getTasks()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM tasks");
    return model;
}
