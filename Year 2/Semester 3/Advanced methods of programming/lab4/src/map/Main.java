package map;

import map.domain.Friendship;
import map.domain.Tuple;
import map.domain.User;
import map.domain.validators.FriendshipValidator;
import map.domain.validators.UserValidator;
import map.repository.Repository;
import map.repository.file.UserRepository;
import map.repository.memory.InMemoryRepository;
import map.service.Network;
import map.service.ServiceFriendships;
import map.service.ServiceUsers;
import map.ui.Console;

// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    private static void start(){
        Repository<String,User> userRepo = new UserRepository(new UserValidator(),"data/utilizatori.txt");
        Repository<Tuple<User,User>, Friendship> friendshipRepo =  new InMemoryRepository<>(new FriendshipValidator());
        ServiceUsers userService = new ServiceUsers(userRepo);
        ServiceFriendships frindshipService = new ServiceFriendships(friendshipRepo);
        Network network = new Network(userService,frindshipService);
        Console console = new Console(network,true);
        console.menu();
    }
    public static void main(String[] args) {
        start();
    }
}