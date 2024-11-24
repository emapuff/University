package Complex;
import static Enum.Operation.MULTIPLY;

public class Inmultire extends ComplexExpression {
    public Inmultire(NumarComplex[] vector) {
        super(MULTIPLY,vector);
    }

    public NumarComplex executeOneOperation(NumarComplex num1, NumarComplex num2){
        return num1.inmultire(num2);
    }
}
