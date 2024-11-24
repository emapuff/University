package Complex;
import Factory.ExpressionFactory;
import Enum.Operation;
import java.util.regex.Pattern;

public class ExpresionParser {
    private final String[] expresions;

    public ExpresionParser(String[] expresions) {
        this.expresions = expresions;
    }

    public boolean verifyExpresion(String expresion) {
        String regex = "^([+-]?\\d+(\\.\\d+)?([+-]\\d*(\\.\\d+)?\\*?i)?)((\\s*[+\\-*/]\\s*[+-]?\\d+(\\.\\d+)?([+-]\\d*(\\.\\d+)?\\*?i)?))*$";
        return Pattern.matches(regex, expresion);
    }


    public ComplexExpression parse(){
        NumarComplex[] numbers = new NumarComplex[(expresions.length + 1) / 2];
        for(int i = 0; i < expresions.length; i = i+2){
            String[] el = expresions[i].split("(?=[+-])", 2);
            float re = Float.parseFloat(el[0]);
            String[] IM = el[1].split("\\*", 2);
            float im;
            if(IM.length == 1){
               im = 1;
            }
            else{
               im = Float.parseFloat(IM[0]);
            }
            numbers[i / 2] = new NumarComplex(re, im);
        }

        String operator = expresions[1];
        return switch (operator){
            case "+" -> ExpressionFactory.getInstance().createComplexExpression(Operation.ADDITION,numbers);
            case "-" -> ExpressionFactory.getInstance().createComplexExpression(Operation.SUBSTRACT, numbers);
            case "*" -> ExpressionFactory.getInstance().createComplexExpression(Operation.MULTIPLY, numbers);
            case "/" -> ExpressionFactory.getInstance().createComplexExpression(Operation.DIVIDE, numbers);
            default -> null;
        };
    }


}
