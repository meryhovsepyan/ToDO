#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H



class TaskManager : public QObject
{
    Q_OBJECT
public:
    explicit TaskManager(QObject *parent = nullptr);

    void addTask(const Task& task);
    void removeTask(int index);
    QVector<Task> tasks() const;

signals:
    void tasksChanged();

private:
    QVector<Task> m_tasks;
};

#endif // TASK_MANAGER_H
