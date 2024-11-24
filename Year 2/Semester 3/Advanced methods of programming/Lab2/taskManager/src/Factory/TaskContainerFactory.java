package Factory;

import Container.ContainterInterface;
import Container.QueueContainer;
import Container.StackContainer;
import Enum.ContainerStrategy;

public class TaskContainerFactory implements Factory{

    private TaskContainerFactory(){}

    private static final TaskContainerFactory instance = new TaskContainerFactory();
    public static TaskContainerFactory getInstance(){
        return instance;
    }

    @Override
    public ContainterInterface createContainer(ContainerStrategy strategy){
        switch(strategy){
            case LIFO ->{
                return new StackContainer();
            }
            case FIFO -> {
                return new QueueContainer();
            }
        }
        return null;
    }
}
