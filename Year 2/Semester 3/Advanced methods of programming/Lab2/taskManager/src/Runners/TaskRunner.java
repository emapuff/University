package Runners;

import Model.Task;

public interface TaskRunner {
    void executeOneTask();
    void executeAll();
    void addTask(Task task);
    boolean hasTask(); //verifica daca mai sunt taskuri de executat
}
