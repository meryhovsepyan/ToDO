#include "include/task.h"

Task::Task(int id, const QString& title, const QString& description, const QString& date, bool status)
    :m_id(id), m_title(title), m_description(description), m_date(date), m_status(status)
{
}

QString Task::title() const
{
    return m_title;
}

int Task::id() const
{
    return m_id;
}

QString Task::description() const
{
    return m_description;
}

QString Task::date() const
{
    return m_date;
}

void Task::setId(int id)
{
    m_id = id;
}

bool Task::status() const
{
    return m_status;
}

void Task::setTitle(const QString& title)
{
    m_title = title;
}

void Task::setDescription(const QString& description)
{
    m_description = description;
}

void Task::setDate(const QString& date)
{
    m_date = date;
}

void Task::setStatus(bool status)
{
    m_status = status;
}
