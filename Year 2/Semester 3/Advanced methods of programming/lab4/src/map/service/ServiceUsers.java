package map.service;
import map.domain.User;
import map.repository.Repository;

import java.util.List;
import java.util.Optional;

public class ServiceUsers implements ServiceAbs<String,User>{
    private final Repository<String,User> userRepo;

    public ServiceUsers(Repository<String,User> userRepo) {
        this.userRepo = userRepo;
    }

    public Optional<User> findUserByEmail(String email) {
        return userRepo.findOne(email);
    }

    public Iterable<User> getEntities() {
        return userRepo.findAll();
    }

    @Override
    public void add(User user) {
        userRepo.save(user);
    }

    public void addUser(String email,String firstName, String lastName){
        User user = new User(firstName,lastName);
        user.setId(email);
        this.add(user);
    }

    public void remove(String email){
        userRepo.delete(email);
    }

    public Optional<User> getOne(String email){
        return userRepo.findOne(email);
    }

    public List<User> getFriends(User user){
        return user.getFriends();
    }







}
