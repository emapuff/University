package Complex;
import static Enum.Operation.ADDITION;

public class Adunare extends ComplexExpression {

    public Adunare(NumarComplex[] vector) {
        super(ADDITION,vector);
    }

    public NumarComplex executeOneOperation(NumarComplex num1, NumarComplex num2) {
        return num1.adunare(num2);
    }
}
