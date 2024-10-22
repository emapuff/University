package ubb.scs.map.service;
import ubb.scs.map.domain.User;
import ubb.scs.map.repository.Repository;

import java.util.List;

public class ServiceUsers implements ServiceAbs<String,User>{
    private final Repository<String,User> userRepo;

    public ServiceUsers(Repository<String,User> userRepo) {
        this.userRepo = userRepo;
    }

    public User findUserByEmail(String email) {
        return userRepo.findOne(email);
    }

    /**
     * @return all users from userRepository
     */
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

    public User getOne(String email){
        return userRepo.findOne(email);
    }

    public List<User> getFriends(User user){
        return user.getFriends();
    }







}
