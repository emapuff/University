package map.repository.file;

import map.domain.User;
import map.domain.validators.Validator;

public class UserRepository extends AbstractFileRepository<String, User>{
    public UserRepository(Validator<User> validator, String fileName) {
        super(validator, fileName);
    }

    @Override
    public User createEntity(String line) {
        String[] splited = line.split(";");
        User u = new User(splited[1], splited[2]);
        u.setId(splited[0]);
        return u;
    }

    @Override
    public String saveEntity(User entity) {
        String s = entity.getId() + ";" + entity.getFirstName()
                + ";" + entity.getLastName();
        return s;
    }
}
