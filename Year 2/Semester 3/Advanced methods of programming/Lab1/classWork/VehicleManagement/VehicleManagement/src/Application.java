import domain.Vehicle;
import repository.VehicleRepository;
import utils.MileageUnit;

public class Application {

	public static void main(String[] args) {

		Vehicle vehicle = new Vehicle("AB17EMA",10.2,2010, MileageUnit.KM);
		VehicleRepository repository = new VehicleRepository();
		repository.addVehicle(vehicle);
	
		for (int i = 0; i < repository.getNumberOfVehicles(); i++) {
			Vehicle retrievedVehicle = repository.getVehicleAtPosition(i);
			retrievedVehicle.printVehicleDetails();
		}
	}

}
