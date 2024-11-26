package org.socialnetworklabseven;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import org.socialnetworklabseven.domain.validators.FriendshipValidator;
import org.socialnetworklabseven.domain.validators.UserValidator;
import org.socialnetworklabseven.repository.database.FriendshipDataBaseRepository;
import org.socialnetworklabseven.repository.database.MessageDataBaseRepository;
import org.socialnetworklabseven.repository.database.PendingRequestsRepository;
import org.socialnetworklabseven.repository.database.UserDataBaseRepository;
import org.socialnetworklabseven.service.BeginningService;
import org.socialnetworklabseven.service.Network;
import org.socialnetworklabseven.service.ServiceFriendships;
import org.socialnetworklabseven.service.ServiceUsers;

import java.io.IOException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        String userName = "postgres";
        String password = "teiubesctati17";
        String url = "jdbc:postgresql://localhost:5432/SocialNetwork";

        UserDataBaseRepository userRepo =
                new UserDataBaseRepository(url, userName, password, new UserValidator());
        PendingRequestsRepository pendingRequestsRepository =
                new PendingRequestsRepository(url, userName, password,userRepo);
        FriendshipDataBaseRepository friendshipRepo =
                new FriendshipDataBaseRepository(url, userName, password,
                        new FriendshipValidator(), userRepo);
        MessageDataBaseRepository messRepo =
                new MessageDataBaseRepository(url,userName,password,userRepo);
        ServiceUsers userService = new ServiceUsers(userRepo);
        ServiceFriendships friendshipService = new ServiceFriendships(friendshipRepo);
        Network network = new Network(userService, friendshipService);
        BeginningService beginningService = new BeginningService(network);
        initView(stage, beginningService,pendingRequestsRepository,network,messRepo);
        stage.setWidth(600);
        stage.setTitle("SocialNetwork");
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }

    private void initView(Stage primaryStage, BeginningService beginningService, PendingRequestsRepository pendingRequestsRepository,Network network,MessageDataBaseRepository messageDataBaseRepository) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("hello-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load());
        primaryStage.setScene(scene);
        HelloController usersController = fxmlLoader.getController();
        usersController.setSocialNetwork(beginningService);
        usersController.setPendingRequestsRepository(pendingRequestsRepository);
        usersController.setNetwork(network);
        usersController.setMessageDataBaseRepository(messageDataBaseRepository);
    }
}
