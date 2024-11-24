

public class Car {
    private int year;
    private double price;

    public Car(int year, double price){
        this.year = year;
        this.price = price;
    }

    public Car(){}

    public int getYear(){
        return year;
    }

    public double getPrice(){
        return price;
    }

    @Override
    public String toString(){
        return "year: " + year + " price:" +price;
    }
}
