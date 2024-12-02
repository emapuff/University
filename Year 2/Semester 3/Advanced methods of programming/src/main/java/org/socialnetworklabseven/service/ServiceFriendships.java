package org.socialnetworklabseven.service;

import  org.socialnetworklabseven.domain.Friendship;
import  org.socialnetworklabseven.domain.Tuple;
import  org.socialnetworklabseven.domain.User;
import org.socialnetworklabseven.domain.pagining.Page;
import org.socialnetworklabseven.domain.pagining.Pageable;
import org.socialnetworklabseven.repository.PagingRepository;
import  org.socialnetworklabseven.repository.Repository;

import java.util.Optional;

public class ServiceFriendships implements
        ServiceAbs<Tuple<User, User>, Friendship>{
    private final PagingRepository<Tuple<User,User>,Friendship> frinedshipRepo;

    public ServiceFriendships(PagingRepository<Tuple<User,User>,
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

    public Page<Friendship> findAllOnPage(String email, Pageable pageable){
        return frinedshipRepo.findAllOnPage(email,pageable);
    }
}
