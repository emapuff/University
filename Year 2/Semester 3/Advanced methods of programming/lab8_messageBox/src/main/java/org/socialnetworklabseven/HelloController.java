package org.socialnetworklabseven;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Modality;
import javafx.stage.Stage;
import org.socialnetworklabseven.domain.User;
import org.socialnetworklabseven.repository.database.MessageDataBaseRepository;
import org.socialnetworklabseven.repository.database.PendingRequestsRepository;
import org.socialnetworklabseven.service.BeginningService;
import org.socialnetworklabseven.service.Network;

import java.io.IOException;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class HelloController {
    Network network;
    BeginningService service;
    ObservableList<User> model = FXCollections.observableArrayList();
    PendingRequestsRepository pendingRequestsRepository;
    MessageDataBaseRepository messageDataBaseRepository;

    public void setMessageDataBaseRepository(MessageDataBaseRepository messageDataBaseRepository) {
        this.messageDataBaseRepository = messageDataBaseRepository;
    }

    @FXML
    TableView<User> tableView;

    @FXML
    TableColumn<User, String> tableUserId;

    @FXML
    TableColumn<User, String> tableUserFirstName;

    @FXML
    TableColumn<User, String> tableUserLastName;

    @FXML
    public void initialize() {
        //tableUserId.setCellValueFactory(new PropertyValueFactory<User, String>("email"));
        tableUserFirstName.setCellValueFactory(new PropertyValueFactory<User, String>("firstName"));
        tableUserLastName.setCellValueFactory(new PropertyValueFactory<User, String>("lastName"));
        tableView.setItems(model);
    }

    @FXML
    public void handleLogIn() {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/org/socialnetworklabseven/LogInController/logInForm.fxml"));
            Scene scene = new Scene(loader.load());
            LogInController logInController = loader.getController();
            logInController.setNetwork(network);
            logInController.setBeginningService(service);
            logInController.setPendingRequestsRepository(pendingRequestsRepository);
            logInController.setMessageDataBaseRepository(messageDataBaseRepository);
            Stage stage = new Stage();
            stage.setScene(scene);
            stage.initModality(Modality.APPLICATION_MODAL);
            stage.setTitle("Log In");
            stage.showAndWait();
        } catch (IOException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText("Something went wrong!");
            alert.setContentText("An error occurred while trying to load the Log In form.");
            alert.showAndWait();
        }
    }


    @FXML void handleSignIn(){
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/signInForm.fxml"));
            Scene scene = new Scene(loader.load());
            SignInController signInController = loader.getController();
            signInController.setNetwork(network);
            signInController.setPendingRequestsRepository(pendingRequestsRepository);
            signInController.setMessageDataBaseRepository(messageDataBaseRepository);
            Stage stage = new Stage();
            stage.setScene(scene);
            stage.initModality(Modality.APPLICATION_MODAL);
            stage.setTitle("Sign In");
            stage.showAndWait();
        } catch (IOException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText("Something went wrong!");
            alert.setContentText("An error occurred while trying to load the Sign In form.");
            alert.showAndWait();
        }
    }

    public void setSocialNetwork(BeginningService serv){
        service = serv;
        initModel();
    }

    public void setNetwork(Network network){
        this.network = network;
    }

    public void setPendingRequestsRepository(PendingRequestsRepository pendingRequestsRepository){
        this.pendingRequestsRepository = pendingRequestsRepository;
    }

    private void initModel(){
        Iterable<User> iterator = service.getUsers();
        List<User> users = StreamSupport.stream(iterator.spliterator(),false)
                .collect(Collectors.toList());
        model.setAll(users);
    }


}
