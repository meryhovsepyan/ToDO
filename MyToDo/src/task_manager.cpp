#include "task_manager.h"

ToDoManager::ToDoManager(QObject *parent)
    : QObject{parent}
{
    m_date = QDate::currentDate();
}
