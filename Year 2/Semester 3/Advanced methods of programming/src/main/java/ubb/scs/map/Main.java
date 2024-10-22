package ubb.scs.map;

import ubb.scs.map.domain.Friendship;
import ubb.scs.map.domain.Tuple;
import ubb.scs.map.domain.User;
import ubb.scs.map.domain.validators.FriendshipValidator;
import ubb.scs.map.domain.validators.UserValidator;
import ubb.scs.map.repository.Repository;
import ubb.scs.map.repository.file.UserRepository;
import ubb.scs.map.repository.memory.InMemoryRepository;
import ubb.scs.map.service.Network;
import ubb.scs.map.service.ServiceFriendships;
import ubb.scs.map.service.ServiceUsers;
import ubb.scs.map.ui.Console;

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