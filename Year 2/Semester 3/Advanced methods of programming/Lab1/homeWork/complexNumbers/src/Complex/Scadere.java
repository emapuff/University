package Complex;
import static Enum.Operation.SUBSTRACT;

public class Scadere extends ComplexExpression {
    public Scadere(NumarComplex[] vector){
        super(SUBSTRACT,vector);
    }

    public NumarComplex executeOneOperation(NumarComplex num1, NumarComplex num2){
        return num1.scaere(num2);
    }
}
