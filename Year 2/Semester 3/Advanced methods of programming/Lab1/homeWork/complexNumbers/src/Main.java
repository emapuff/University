import Complex.*;

public class Main {
    public static void main(String[] args) {
        String entireArgument = String.join(" ", args);
        ExpresionParser parser = new ExpresionParser(args);
        System.out.println(entireArgument);
        if(!parser.verifyExpresion(entireArgument)){
            System.out.println("Invalid expresion");
        } else{
            ComplexExpression expre = parser.parse();
            NumarComplex result = expre.execute();
            System.out.println("Result: " + result);
        }
    }
}