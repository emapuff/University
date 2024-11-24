
public class AudiCar extends Car{
    private String market;

    public AudiCar(int year, int price, String market) {
        super(year, price); //apelam constructorul de la clasa Car
        this.market = market;
    }

    @Override
    public String toString() {
        return super.toString() + " " + this.market; //apelam in mod explicit funcia din calsa mostenita
    }
}
