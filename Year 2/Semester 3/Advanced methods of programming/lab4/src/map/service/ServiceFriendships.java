package map.service;

import map.domain.Friendship;
import map.domain.Tuple;
import map.domain.User;
import map.repository.Repository;

import java.util.Optional;

public class ServiceFriendships implements
        ServiceAbs<Tuple<User, User>, Friendship>{
    private final Repository<Tuple<User,User>,Friendship> frinedshipRepo;

    public ServiceFriendships(Repository<Tuple<User,User>,
            Friendship> frinedshipRepo) {
        this.frinedshipRepo = frinedshipRepo;
    }

    @Override
    public Iterable<Friendship> getEntities(){
        return frinedshipRepo.findAll();
    }

    @Override
    public void add(Friendship friendship){
        frinedshipRepo.save(friendship);
    }

    public void delete(Tuple<User,User> user){
        frinedshipRepo.delete(user);
    }

    public Optional<Friendship> getOne(Tuple<User,User> user){
        return frinedshipRepo.findOne(user);
    }
}
