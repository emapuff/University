package Factory;
import Enum.Operation;
import Complex.*;

public class ExpressionFactory {

    private static ExpressionFactory instance;

    public static ExpressionFactory getInstance() {
        if (instance == null) {
            instance = new ExpressionFactory();
        }
        return instance;
    }

    public ComplexExpression createComplexExpression(Operation operation, NumarComplex[] args) {
        switch (operation) {
            case ADDITION -> {
                return new Adunare(args);
            }
            case SUBSTRACT -> {
                return new Scadere(args);
            }
            case MULTIPLY -> {
                return new Inmultire(args);
            }
            case DIVIDE -> {
                return new Impartire(args);
            }
            default -> {
                return null;
            }
        }
    }


}
