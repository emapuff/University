package Model;

public class QuickSort extends AbstactSorter{
    @Override
    public void sort(int[] numbers) {
        quickSort(numbers, 0, numbers.length-1);
    }

    public void quickSort(int[] numere, int begin, int end) {
        if (begin < end) {
            int partitionIndex = partition(numere, begin, end);

            quickSort(numere, begin, partitionIndex - 1);
            quickSort(numere, partitionIndex + 1, end);
        }
    }

    private int partition(int[] numere, int begin, int end) {
        int pivot = numere[end];
        int i = begin - 1;

        for (int j = begin; j < end; j++) {
            if (numere[j] <= pivot) {
                i++;
                int aux = numere[i];
                numere[i] = numere[j];
                numere[j] = aux;
            }
        }

        int aux = numere[i + 1];
        numere[i + 1] = numere[end];
        numere[end] = aux;

        return i + 1;
    }
}
