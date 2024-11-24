package Container;

import Model.Task;

import java.util.Stack;

public class StackContainer extends AbstractContainer{

    public StackContainer(){
        super();
    }

    @Override
    public Task remove(){
        if(!isEmpty()){
            return tasks.remove(size()-1);
        }
        return null;
    }

}
