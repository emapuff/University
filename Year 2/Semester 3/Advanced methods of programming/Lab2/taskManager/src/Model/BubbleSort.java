package Model;

public class BubbleSort extends AbstactSorter{
    @Override
    public void sort(int[] numere){
        for(int i=0; i<numere.length; i++){
            for(int j=0; j<numere.length -1 ; j++){
                if(numere[j] > numere[j+1]){
                    numere[j] += numere[j+1];
                    numere[j+1] = numere[j] - numere[j+1];
                    numere[j] = numere[j] - numere[j+1];
                }
            }
        }
    }
}
