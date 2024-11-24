package Complex;

import Enum.Operation;
import java.util.Arrays;

public abstract class ComplexExpression {
    private Operation operation;
    private NumarComplex[] vector;

    public ComplexExpression(Operation operation, NumarComplex[] vector) {
        this.operation = operation;
        this.vector = vector;
    }

    protected abstract  NumarComplex executeOneOperation(NumarComplex num1, NumarComplex num2);

    public NumarComplex execute(){

        NumarComplex result = vector[0];
        for(int i=1; i<vector.length ; i++){
            result = executeOneOperation(result,vector[i]);
        }
        return result;
    }


}
