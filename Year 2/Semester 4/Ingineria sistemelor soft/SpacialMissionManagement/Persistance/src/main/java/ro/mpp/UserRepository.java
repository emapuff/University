package ro.mpp;

public interface UserRepository extends CrudRepository<Integer, User> {
    User findByEmailAndPassword(String email, String pass);
}
