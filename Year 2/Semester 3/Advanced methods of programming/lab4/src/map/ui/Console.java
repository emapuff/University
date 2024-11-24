package map.ui;

import map.domain.Friendship;
import map.domain.User;
import map.domain.validators.ValidationException;
import map.service.Network;

import java.util.List;
import java.util.Optional;
import java.util.Scanner;
import java.util.concurrent.atomic.AtomicInteger;

public class Console {
    private final Network network;
    private final Scanner scanner;
    private final boolean isFile;

    public Console(Network network, boolean isFile) {
        this.network = network;
        this.isFile = isFile;
        scanner = new Scanner(System.in);
    }

    private void printAllUsers(){
        AtomicInteger number = new AtomicInteger(0);
        network.getAllUsers().forEach(u -> number.incrementAndGet());
        if(number.get()!=0) {
            System.out.println("Users LIST: ");
            network.getAllUsers().forEach(user -> System.out.
                    println(user.toString()));
        }
        else{
            System.out.println("List of users is empty.\n");
        }
    }

    private void printAllFriendships(){
        AtomicInteger number = new AtomicInteger(0);
        network.getAllFriendships().forEach(u-> number
                .incrementAndGet());
        if(number.get()!=0) {
            System.out.println("Friendships LIST: ");
            network.getAllFriendships().forEach(friendship ->
                    System.out.println(friendship.toString()));
        }
        else{
            System.out.println("List of friendships is empty.\n");
        }
    }

    private void deleteUserUI(){
        System.out.print("Insert user's Email: ");
        try{
            String email = scanner.next();
            Optional<User> user = network.getOne(email);
            if (user.isEmpty()) {
                System.out.println("User not found");
            }
            else{
                network.deleteUser(email);
                System.out.println(user + " was successfully deleted." );
            }
        }
        catch (IllegalArgumentException e) {
            throw new RuntimeException("An error occurred", e);
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    private void addFriendUI(){
        try{
            System.out.print("Insert user's Email: ");
            String email1 = scanner.next();
            System.out.print("Insert his friend Email: ");
            String email2 = scanner.next();
            Friendship friendship = network.addFriendship(email1, email2);
            if(friendship != null){
                System.out.println("Friendship was successfully added.");
            }
            else{
                System.out.println("Friendship already exists.");
            }
        }
        catch (IllegalArgumentException e) {
            throw new RuntimeException("An error occurred", e);
        }
        catch (ValidationException e) {
            System.out.println(e.getMessage());
        }
    }

    private void deleteFriendUI(){
        try{
            System.out.print("Insert user's Email: ");
            String email1 = scanner.next();
            System.out.print("Insert his friend Email: ");
            String email2 = scanner.next();
            Optional<Friendship> friendship = network.removeFriendship(email1, email2);
            if(friendship.isPresent()){
                System.out.println("Friendship does not exist.");
            }
            else{
                System.out.println("Friendship was successfully deleted.");
            }
        }
        catch (IllegalArgumentException e) {
            throw new RuntimeException("An error occurred", e);
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    private void printFriends(){
        System.out.println("Insert user's Emails: ");
        try{
            String email1 = scanner.next();
            List<User> friends = network.getFriends(email1);
            if(friends == null){
                System.out.println("User not found.");
            }
            else{
                if(friends.isEmpty()){
                    System.out.println("No friends found.");
                }
                else {
                    System.out.println("User's friends list: ");
                    for (User user : friends) {
                        System.out.println(user);
                    }
                }
            }
        }
        catch (IllegalArgumentException e) {
            throw new RuntimeException("An error occurred at the argument", e);
        }
    }

    private void communitiesNumberUI(){
        int comunitiesNumber = network.communitiesNumber();
        System.out.println("Number of communities is: " + comunitiesNumber);
    }

    private void biggestCommunityiUI(){
        List<User> biggestCommunity = network.biggestComunity();
        if(biggestCommunity.isEmpty()){
            System.out.println("There are not comunities.");
        }
        else {
            System.out.println("The biggest community is: ");
            for (User u: biggestCommunity) {
                System.out.println(network.getOne(u.getId()));
            }
        }
    }


    public void printMenu(){
        System.out.println("Options are: \n");
        System.out.println("*1* print_users: Show all users");
        System.out.println("*2* print_friendships: Show all friendships");
        System.out.println("*3* del_user: Delete one user");
        System.out.println("*4* print_friends: Show all friends for an user");
        System.out.println("*5* add_friend: Add one friendship");
        System.out.println("*6* del_friend: Delete one friendship");
        System.out.println("*7* com_number: Show number of comunity");
        System.out.println("*8* com_biggest: Show the biggest comunity");
        System.out.println("*9* exit: Exit");
    }

    public void menu(){
        System.out.println("------------PuffMess Network------------");
        while(true){
            printMenu();
            System.out.println("\n Choose one option:");
            String option;
            Scanner sc = new Scanner(System.in);
            option = sc.nextLine();
            option = option.toLowerCase();
            switch (option) {
                case "print_users" -> printAllUsers();
                case "print_friendships" -> printAllFriendships();
                case "del_user" -> deleteUserUI();
                case "add_friend" -> addFriendUI();
                case "del_friend" -> deleteFriendUI();
                case "print_friends" -> printFriends();
                case "com_number" -> communitiesNumberUI();
                case "com_biggest" -> biggestCommunityiUI();
                case "exit" -> System.exit(0);
                default -> System.out.println("||||| Option not recognized. ||||||");
            }
        }
    }
}
