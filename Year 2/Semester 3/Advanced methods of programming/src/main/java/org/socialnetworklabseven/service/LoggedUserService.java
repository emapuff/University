package org.socialnetworklabseven.service;

import org.socialnetworklabseven.domain.Friendship;
import org.socialnetworklabseven.domain.MessageDTO;
import org.socialnetworklabseven.domain.Tuple;
import org.socialnetworklabseven.domain.User;
import org.socialnetworklabseven.domain.pagining.Page;
import org.socialnetworklabseven.domain.pagining.Pageable;
import org.socialnetworklabseven.repository.database.MessageDataBaseRepository;
import org.socialnetworklabseven.repository.database.PendingRequestsRepository;

import java.sql.SQLException;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class LoggedUserService {
    private final Network network;
    private final User loggedUser;
    private final PendingRequestsRepository pendings;
    private MessageDataBaseRepository messageRepo;

    public LoggedUserService(Network network, User loggedUser, PendingRequestsRepository pendings){
        this.network = network;
        this.loggedUser=loggedUser;
        this.pendings = pendings;
    }

    public void setMessageRepo(MessageDataBaseRepository messageRepo) {
        this.messageRepo=messageRepo;
    }

    public Iterable<User> getUsers(){
        return network.getAllUsers();
    }

    public List<User> getFriendships(){
        List<User> friendships = network.getFriends(loggedUser.getId());
        for (User user : friendships) {
            System.out.println(user);
        }
        return network.getFriends(loggedUser.getId());
    }
    public List<Tuple<User, LocalDateTime>> getPendingRequests() throws SQLException {
            List<Tuple<User, LocalDateTime>> pend = pendings.findAllForOneUser(loggedUser);
            if(pend.isEmpty()){
                return new ArrayList<>();
            }
            return pendings.findAllForOneUser(loggedUser);
    }

    public User getLoggedUser() {
        return loggedUser;
    }

    public void deleteUser(){
       network.deleteUser(loggedUser.getId());
    }

    public void deleteFriendship(User userFriend){
       network.removeFriendship(loggedUser.getId(), userFriend.getId());
    }

    public void pendFriendRequest(User user){
        pendings.save(loggedUser,user);
    }

    public void acceptFriendRequest(User user){
       network.addFriendship(loggedUser.getId(), user.getId());
       pendings.delete(loggedUser,user);
    }

    public List<User> getOtherUsers(){
        Iterable <User> all = this.getUsers();
        List<User> otherUsers = new ArrayList<>();
        for (User user : all) {
            if(!user.getFriends().contains(loggedUser.getId())){
                otherUsers.add(user);
            }
        }
        return otherUsers;
    }

    public Optional<User> getByEmail(String email){
        return this.network.getOne(email);
    }

    public List<User> getUsersThatSentMessages(){
        return messageRepo.findMessagedUsers(loggedUser);
    }

    public List<MessageDTO> getListMessages(User user,User friend){
        return messageRepo.findAllMessages(user,friend);
    }

    public void sendMessage(User friend,String message){
        messageRepo.save(loggedUser,friend,message);
    }

    public Page<User> getPageUser(Pageable pageable){
        return network.getFriendshipPaged(loggedUser.getId(), pageable);
    }
}
