package Container;

import Model.Task;

public interface ContainterInterface {
    Task remove();
    void add(Task task);
    int size();
    boolean isEmpty();
}
