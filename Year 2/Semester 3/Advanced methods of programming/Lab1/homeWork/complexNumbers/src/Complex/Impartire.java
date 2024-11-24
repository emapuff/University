package Complex;
import static Enum.Operation.DIVIDE;

public class Impartire extends ComplexExpression{
    public Impartire(NumarComplex[] vector){
        super(DIVIDE,vector);
    }
    public NumarComplex executeOneOperation(NumarComplex num1, NumarComplex num2){
        return num1.impartire(num2);
    }
}
