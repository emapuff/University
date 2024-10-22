package ubb.scs.map.repository.file;

import ubb.scs.map.domain.User;
import ubb.scs.map.domain.validators.Validator;

public class UserRepository extends AbstractFileRepository<String, User>{
    public UserRepository(Validator<User> validator, String fileName) {
        super(validator, fileName);
    }

    /**
     * @param line - the line to be parsed
     * @return the entity created from the line
     */
    @Override
    public User createEntity(String line) {
        String[] splited = line.split(";");
        User u = new User(splited[1], splited[2]);
        u.setId(splited[0]);
        return u;
    }

    /**
     * @param entity - the entity to be parsed
     * @return the line created from the entity
     */
    @Override
    public String saveEntity(User entity) {
        String s = entity.getId() + ";" + entity.getFirstName() + ";" + entity.getLastName();
        return s;
    }
}
