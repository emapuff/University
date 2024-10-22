package ubb.scs.map.service;

import ubb.scs.map.domain.Friendship;
import ubb.scs.map.domain.Tuple;
import ubb.scs.map.domain.User;
import ubb.scs.map.repository.Repository;

public class ServiceFriendships implements ServiceAbs<Tuple<User, User>, Friendship>{
    private final Repository<Tuple<User,User>,Friendship> frinedshipRepo;

    public ServiceFriendships(Repository<Tuple<User,User>,Friendship> frinedshipRepo) {
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

    public Friendship getOne(Tuple<User,User> user){
        return frinedshipRepo.findOne(user);
    }




}
