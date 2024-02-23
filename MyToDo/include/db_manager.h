#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QDir>
#include <QStandardPaths>

class DBManager : public QObject
{
    Q_OBJECT
public:
    explicit DBManager(QObject *parent = nullptr);
    ~DBManager();
    void init();
    void createTable();
    int insertTask(const QString &title, const QString &description, const QString &date, bool status);
    bool deleteTask(int taskId);
    bool updateTitle(int taskId, const QString &title);
    bool updateDescription(int taskId, const QString &description);
    bool updateDate(int taskId, const QString &date);
    bool updateStatus(int taskId, bool status);

    QSqlQueryModel* getTasks();

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
