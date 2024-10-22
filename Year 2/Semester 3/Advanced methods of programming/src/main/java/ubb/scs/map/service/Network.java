package ubb.scs.map.service;

import ubb.scs.map.domain.Friendship;
import ubb.scs.map.domain.Tuple;
import ubb.scs.map.domain.User;

import java.time.LocalDateTime;
import java.util.*;

public class Network {
    private final ServiceUsers userService;
    private final ServiceFriendships friendshipService;
    private  final Map<User, List<User>> graph;

    public Network(ServiceUsers userService, ServiceFriendships friendshipService) {
        this.userService = userService;
        this.friendshipService = friendshipService;
        this.graph = new HashMap<>();
    }

    public void addToGraph(User userHost, User userFriend){
        graph.computeIfAbsent(userHost, k -> new ArrayList<>()).add(userFriend);
    }

    public Friendship addFriendship(String email1,String email2){
        User user1 = userService.getOne(email1);
        User user2 = userService.getOne(email2);
        if(user1 != null && user2 != null){
            user1.addFriend(user2);
            user2.addFriend(user1);
            //add them to the list
            Friendship friendship = new Friendship(user1,user2);
            friendship.setId(new Tuple<>(user1,user2));
            friendship.setDate(LocalDateTime.now());
            friendshipService.add(friendship); //add the friendship
            this.addToGraph(user1,user2);
            this.addToGraph(user2,user1);
            return friendship;
        }else
            return null;
    }

    public void deleteFromGraph(User user1, User user2){
        if (graph.containsKey(user1)) {
            graph.get(user1).remove(user2);
        }

        if (graph.containsKey(user2)) {
            graph.get(user2).remove(user1);
        }
    }

    public Friendship removeFriendship(String email1,String email2){
        String emailMin = (email1.compareTo(email2) < 0) ? email1 : email2;
        String emailMax = (email1.compareTo(email2) > 0) ? email1 : email2;
        User user1 = userService.getOne(emailMin);
        User user2 = userService.getOne(emailMax);
        Tuple<User,User> emailTuple = new Tuple<>(user1,user2);

        if(user1 != null && user2 != null){
            user1.removeFriend(user2); //delete from each
            user2.removeFriend(user1);
            friendshipService.delete(emailTuple); //delete the friendhip
            this.deleteFromGraph(user1,user2);
            return friendshipService.getOne(emailTuple);
        }
        else return null;
    }

    public void deleteUser(String email){
        User user = userService.getOne(email);
        if(user != null){
            Iterable<User> iterator = userService.getEntities();
            for(User user2 : iterator){
                user2.removeFriend(user);
                this.deleteFromGraph(user2,user);
                //remove from each friend list
            }
            userService.remove(email); //delete from the system
        }
    }

    private List<User> BFS(User user, HashMap<User, Boolean> visited){
        Queue<User> queue = new LinkedList<>();
        List<User> result = new ArrayList<>();
        queue.add(user);
        visited.put(user, true);

        while(!queue.isEmpty()){
            User node = queue.poll();
            result.add(node);
            List<User> prieteni = userService.getFriends(node);
            for(User u : prieteni){
                if(!visited.get(u)){
                    visited.put(u, Boolean.TRUE);
                    queue.add(u);
                }
            }
        }
        System.out.println();
        return result;
    }


    public int communitiesNumber(){
        int number = 0;
        HashMap<User, Boolean> visited = new HashMap<>();
        Iterable<User> users = userService.getEntities();

        for(User user : users){
            visited.put(user, Boolean.FALSE);
        }

        for(User user : visited.keySet()){
            if(!visited.get(user)){
                this.BFS(user,visited);
                number++;
            }
        }

        return number;
    }

    public List<User> biggestComunity(){
        HashMap<User, Boolean> visited = new HashMap<>();
        Iterable<User> users = userService.getEntities();
        List<User> result = new ArrayList<>();
        for(User u : users){
            visited.put(u, Boolean.FALSE);
        }
        for(User u : visited.keySet()){
            if(!visited.get(u)){
                List<User> posibleResult = BFS(u,visited);
                if(posibleResult.size() >= result.size()){
                    result = posibleResult;
                }
            }
        }
        return result;
    }

    public Iterable<Friendship> getAllFriendships(){
        return friendshipService.getEntities();
    }

    public Iterable<User> getAllUsers(){
        return userService.getEntities();
    }

    public User getOne(String email){
        return userService.getOne(email);
    }

    public List<User> getFriends(String email){
        User user = userService.getOne(email);
        return userService.getFriends(user);
    }

}
