package Runners;

import Container.ContainterInterface;
import Factory.TaskContainerFactory;
import Enum.ContainerStrategy;
import Model.Task;

public class StrategyTaskRunner implements TaskRunner {

    private ContainterInterface container;

    public StrategyTaskRunner(ContainerStrategy strategy) {
        this.container = TaskContainerFactory.getInstance().createContainer(strategy);
    }

    @Override
    public void executeOneTask() {
        if (hasTask()) {
            Task removedTask = container.remove();
            removedTask.execute();
        }
        else {
            System.out.println("There are no tasks!");
        }
    }

    @Override
    public void executeAll() {
        while (hasTask()) {
            executeOneTask();
        }
    }

    @Override
    public void addTask(Task t) {
        container.add(t);
    }

    @Override
    public boolean hasTask() {
        return !container.isEmpty();
    }

}
