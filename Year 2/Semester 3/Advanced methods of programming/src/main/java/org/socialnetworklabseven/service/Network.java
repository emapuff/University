package org.socialnetworklabseven.service;

import javafx.beans.Observable;
import org.socialnetworklabseven.domain.Friendship;
import  org.socialnetworklabseven.domain.Tuple;
import  org.socialnetworklabseven.domain.User;
import org.socialnetworklabseven.domain.pagining.Page;
import org.socialnetworklabseven.domain.pagining.Pageable;

import java.sql.SQLException;
import java.time.LocalDateTime;
import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class Network {
    private final ServiceUsers userService;
    private final ServiceFriendships friendshipService;
    private  final Map<User, List<User>> graph;

    public Network(ServiceUsers userService,
                   ServiceFriendships friendshipService) {
        this.userService = userService;
        this.friendshipService = friendshipService;
        this.graph = new HashMap<>();
    }

    public void addToGraph(User userHost, User userFriend){
        graph.computeIfAbsent(userHost, k -> new ArrayList<>()).add(userFriend);
    }

    public Friendship addFriendship(String email1, String email2) {
        Optional<User> optionalUser1 = userService.getOne(email1);
        Optional<User> optionalUser2 = userService.getOne(email2);
        if (optionalUser1.isPresent() && optionalUser2.isPresent()) {
            User user1 = optionalUser1.get();
            User user2 = optionalUser2.get();
            user1.addFriend(user2);
            user2.addFriend(user1);
            Friendship friendship = new Friendship(user1, user2);
            friendship.setId(new Tuple<>(user1, user2));
            friendship.setDate(LocalDateTime.now());
            friendshipService.add(friendship);
            this.addToGraph(user1, user2);
            this.addToGraph(user2, user1);
            return friendship;
        } else {
            return null;
        }
    }

    public void deleteFromGraph(User user1, User user2){
        if (graph.containsKey(user1)) {
            graph.get(user1).remove(user2);
        }
        if (graph.containsKey(user2)) {
            graph.get(user2).remove(user1);
        }
    }

    public Optional<Friendship> removeFriendship(String email1,
                                                 String email2) {
        String emailMin = (email1.compareTo(email2) < 0)
                ? email1 : email2;
        String emailMax = (email1.compareTo(email2) > 0)
                ? email1 : email2;

        Optional<User> optionalUser1 = userService.getOne(emailMin);
        Optional<User> optionalUser2 = userService.getOne(emailMax);
        System.out.println(optionalUser1);
        System.out.println(optionalUser2);
        if (optionalUser1.isPresent() && optionalUser2.isPresent()) {
            User user1 = optionalUser1.get();
            User user2 = optionalUser2.get();
            user1.removeFriend(user2);
            user2.removeFriend(user1);
            Tuple<User, User> emailTuple = new Tuple<>(user1, user2);
            System.out.println(emailTuple);
            friendshipService.delete(emailTuple);
            this.deleteFromGraph(user1, user2);
            return friendshipService.getOne(emailTuple);
        } else {
            return Optional.empty();
        }
    }

    public void deleteUser(String email){
        Optional<User> user = userService.getOne(email);
        if(user.isPresent()){
            Iterable<User> iterator = userService.getEntities();
            iterator.forEach(user2 ->{
                user2.removeFriend(user.orElse(null));
                this.deleteFromGraph(user2, user.orElse(null));
            });
            userService.remove(email);
        }
    }

    public List<User> BFS(User user, Map<User, Boolean> visited){
        Queue<User> queue = new LinkedList<>();
        List<User> result = new ArrayList<>();
        queue.add(user);
        visited.put(user, true);
        while(!queue.isEmpty()){
            User node = queue.poll();
            result.add(node);
            List<User> prieteni = userService.getFriends(node);
            prieteni.forEach(u ->{
                if(!visited.get(u)){
                    visited.put(u, Boolean.TRUE);
                    queue.add(u);
                }
            });
        }
        System.out.println();
        return result;
    }

    public int communitiesNumber(){
        AtomicInteger number = new AtomicInteger(0);
        HashMap<User, Boolean> visited = new HashMap<>();
        Iterable<User> users = userService.getEntities();
        users.forEach(user -> visited.put(user, Boolean.FALSE));
        visited.keySet().forEach(user -> {
            if (!visited.get(user)) {
                this.BFS(user, visited);
                number.incrementAndGet();
            }
        });
        return number.get();
    }

    public List<User> biggestComunity() {
        Map<User, Boolean> visited = StreamSupport
                .stream(userService.getEntities().spliterator(), false)
                .collect(Collectors.toMap(user -> user, user -> Boolean.FALSE));
        return visited.keySet().stream()
                .filter(u -> !visited.get(u))
                .map(u -> BFS(u, visited))
                .max(Comparator.comparingInt(List::size))
                .orElse(new ArrayList<>());
    }

    public Iterable<Friendship> getAllFriendships(){
        return friendshipService.getEntities();
    }

    public Iterable<User> getAllUsers(){
        return userService.getEntities();
    }

    public Optional<User> getOne(String email){
        return userService.getOne(email);
    }

    public List<User> getFriends(String email){
        Iterable<Friendship> friendships = friendshipService.getEntities();
        List<User> result = new ArrayList<>();
        for(Friendship friendship : friendships){
           if( friendship.getU2().getId().equals(email)){
               result.add(friendship.getU1());
           } else if( friendship.getU1().getId().equals(email)){
               result.add(friendship.getU2());
           }
        }
        return result;
    }

    public void addUser(User user){
        System.out.println("Network");
        userService.add(user);
    }

    public Page<User> getFriendshipPaged(String email, Pageable pageable){
        try {
            Page<Friendship> friends = friendshipService.findAllOnPage(email, pageable);
            List<User> users = friends.getContent().stream()
                    .map(friendship -> {
                        if (!friendship.getU1().equals(email)) {
                            return friendship.getU1();
                        } else {
                            return friendship.getU2();
                        }
                    })
                    .toList();
            return new Page<>(users,friends.getTotalNumberOfElements());
        }catch (Exception e){
            System.out.println("Eroare la Page<User>");
        }
        return null;
    }
}
