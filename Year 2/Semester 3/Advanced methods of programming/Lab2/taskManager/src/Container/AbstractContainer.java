package Container;

import Model.Task;

import java.util.ArrayList;

public abstract class AbstractContainer implements ContainterInterface{
    protected ArrayList<Task> tasks;

    public AbstractContainer() {
        tasks = new ArrayList<>();
    }

    @Override
    public void add(Task task) {
        tasks.add(task);
    }

    @Override
    public int size(){
        return tasks.size();
    }

    @Override
    public boolean isEmpty(){
        return tasks.isEmpty();
    }

}
