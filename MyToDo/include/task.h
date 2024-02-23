#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QDate>

class Task
{
public:
    Task() = default;
    Task(int id, const QString& title, const QString& description, const QString& date, bool status = false);

    QString title() const;
    QString description() const;
    QString date() const;
    bool status() const;
    int id() const;

    void setTitle(const QString& title);
    void setDescription(const QString& description);
    void setDate(const QString& date);
    void setStatus(bool status);
    void setId(int id);

private:
    int m_id = 0;
    QString m_title;
    QString m_description;
    QString m_date;
    bool m_status;
};

#endif // TASK_H
