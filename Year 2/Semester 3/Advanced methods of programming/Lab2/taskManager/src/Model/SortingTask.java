package Model;
import Enum.SortingStrategy;

public class SortingTask extends Task {

    private AbstactSorter abstactSorter;
    private final int[] numere;
    private final SortingStrategy sortStrategy;

    public SortingTask(String taskId, String descriere, int[] numere, SortingStrategy sortStrategy){
        super(taskId, descriere);
        this.numere = numere;
        this.sortStrategy = sortStrategy;

        switch (sortStrategy){
            case QUICKSORT -> abstactSorter = new QuickSort();
            case BUBBLESORT -> abstactSorter = new BubbleSort();
        }
    }

    @Override
    public void execute() {
        abstactSorter.sort(numere);
        for (Integer i : numere) {
            System.out.println(i);
        }
    }
}
