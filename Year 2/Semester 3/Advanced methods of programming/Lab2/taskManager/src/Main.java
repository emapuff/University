import Model.MessageTask;
import Model.QuickSort;
import Model.SortingTask;
import Runners.DelayTaskRunner;
import Runners.PrinterTaskRunner;
import Runners.StrategyTaskRunner;
import Runners.TaskRunner;


import java.time.LocalDateTime;
import java.util.ArrayList;

import static Enum.SortingStrategy.BUBBLESORT;
import static Enum.SortingStrategy.QUICKSORT;
import static Enum.ContainerStrategy.FIFO;
import static Enum.ContainerStrategy.LIFO;

public class Main {
    public static void populateData(ArrayList<MessageTask> tasks) {
        MessageTask messageTask1 = new MessageTask("Salut!", "Dan", "Maria", LocalDateTime.of(2024, 10, 1, 6, 29), "1", "good job");
        MessageTask messageTask2 = new MessageTask("Bravo!", "Ion", "Ioana", LocalDateTime.of(2024, 10, 1, 7, 29), "2", "good job");
        MessageTask messageTask3 = new MessageTask("Cum mai esti?", "Ion", "Ana", LocalDateTime.of(2024, 10, 1, 8, 29), "3", "good job");
        MessageTask messageTask4 = new MessageTask("La revedere!", "Ion", "Ioana", LocalDateTime.of(2024, 10, 1, 9, 29), "4", "good job");
        MessageTask messageTask5 = new MessageTask("Salut!", "Dan", "Maria", LocalDateTime.of(2024, 10, 1, 10, 29), "5", "good job");
        tasks.add(messageTask1);
        tasks.add(messageTask2);
        tasks.add(messageTask3);
        tasks.add(messageTask4);
        tasks.add(messageTask5);
    }
    public static void main(String[] args) {
        System.out.println(("~~~~~~~~ Mesaje ~~~~~~~~"));

        ArrayList<MessageTask> listOfMesssages = new ArrayList<>();
        populateData(listOfMesssages);

        for (MessageTask message : listOfMesssages) {
            System.out.println(message.toString());
        }

        System.out.println("~~~~~~~~ Sortare ~~~~~~~~");
        System.out.println("Quicksort: ");
        SortingTask sortingTaskQuick = new SortingTask("1","TEME",new int[]{9, -1, 4, 6, 78, 3},QUICKSORT);
        sortingTaskQuick.execute();
        System.out.println("BubbleSort: ");
        SortingTask sortingTaskBubble = new SortingTask("1","TEME",new int[]{9, -1, 4, 6, 78, 3},BUBBLESORT);
        sortingTaskBubble.execute();
        // Scrieți un program de test care creeaza un vector de task-ri de tipul
        // MessageTask si le executa, via un obiect de tipul StrategyTaskRunner,
        // folosind strategia specificata ca parametru in linia de comanda. (main(String[] args).

        // Execution via Strategy Task Runner
        StrategyTaskRunner strategyTaskRunner = new StrategyTaskRunner(LIFO);
        listOfMesssages.forEach(element -> {
            strategyTaskRunner.addTask(element);
        });

        strategyTaskRunner.executeOneTask();
        strategyTaskRunner.executeAll();
        strategyTaskRunner.executeOneTask();

        System.out.println("~~~~~~~~Printer~~~~~~~~~");
        // Execution via Decorator
        StrategyTaskRunner strategyTaskRunnerWithDecorator = new StrategyTaskRunner(FIFO);
        listOfMesssages.forEach(element ->{
            strategyTaskRunnerWithDecorator.addTask(element);
        });
        TaskRunner runner = new PrinterTaskRunner(strategyTaskRunnerWithDecorator);
        runner.executeOneTask();

        System.out.println("~~~~~~~~Delay~~~~~~~~~");
        StrategyTaskRunner strategyDelayTaskRunner = new StrategyTaskRunner(FIFO);
        DelayTaskRunner delayTaskRunner = new DelayTaskRunner(strategyDelayTaskRunner);
        PrinterTaskRunner printerTaskRunner = new PrinterTaskRunner(delayTaskRunner);
        ArrayList<MessageTask> tasks = new ArrayList<>();
        populateData(tasks);
        printerTaskRunner.addTask(tasks.get(0));
        printerTaskRunner.addTask(tasks.get(1));
        printerTaskRunner.addTask(tasks.get(2));
        printerTaskRunner.executeAll();

    }

}