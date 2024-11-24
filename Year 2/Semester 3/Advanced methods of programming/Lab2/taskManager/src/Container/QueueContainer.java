package Container;

import Model.Task;

public class QueueContainer extends AbstractContainer{
    public QueueContainer() {
        super();
    }

    @Override
    public Task remove(){
        if(isEmpty()) return null;
        else{
            return tasks.remove(0);
        }
    }
}
