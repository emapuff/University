package map;

import map.domain.Friendship;
import map.domain.Tuple;
import map.domain.User;
import map.domain.validators.FriendshipValidator;
import map.domain.validators.UserValidator;
import map.repository.Repository;
import map.repository.database.FriendshipDataBaseRepository;
import map.repository.database.UserDataBaseRepository;
import map.repository.file.UserRepository;
import map.repository.memory.InMemoryRepository;
import map.service.Network;
import map.service.ServiceFriendships;
import map.service.ServiceUsers;
import map.ui.Console;

import java.util.Scanner;

// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    private static void start(){
        Scanner scanner = new Scanner(System.in);
        System.out.println("Introduceti modul in care doriti sa rulati Reteaua(file/db):");
        String type = scanner.next();
        if(type.equals("file")) {
            Repository<String, User> userRepo =
                    new UserRepository(new UserValidator(), "data/utilizatori.txt");
            Repository<Tuple<User, User>, Friendship> friendshipRepo =
                    new InMemoryRepository<>(new FriendshipValidator());
            ServiceUsers userService = new ServiceUsers(userRepo);
            ServiceFriendships frindshipService = new ServiceFriendships(friendshipRepo);
            Network network = new Network(userService, frindshipService);
            Console console = new Console(network, true);
            console.menu();
        }
        else if(type.equals("db")) {
            String username="postgres";
            String pasword="teiubesctati17";
            String url="jdbc:postgresql://localhost:5432/SocialNetwork";
            UserDataBaseRepository userRepo =
                    new UserDataBaseRepository(url,username,pasword,new UserValidator());
            FriendshipDataBaseRepository friendshipRepo =
                    new FriendshipDataBaseRepository(url,username,pasword,
                            new FriendshipValidator(), userRepo);
            ServiceUsers userService = new ServiceUsers(userRepo);
            ServiceFriendships frindshipService = new ServiceFriendships(friendshipRepo);
            Network network = new Network(userService, frindshipService);
            Console console = new Console(network, false);
            console.menu();

        } else{
            throw new RuntimeException("Unrecognized type");
        }
    }
    public static void main(String[] args) {
        start();
    }
}