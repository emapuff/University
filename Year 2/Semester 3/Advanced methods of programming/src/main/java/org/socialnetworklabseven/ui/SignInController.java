package org.socialnetworklabseven.ui;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.TextField;
import javafx.scene.control.PasswordField;
import javafx.stage.Stage;
import org.socialnetworklabseven.domain.User;
import org.socialnetworklabseven.repository.database.MessageDataBaseRepository;
import org.socialnetworklabseven.repository.database.PendingRequestsRepository;
import org.socialnetworklabseven.service.LoggedUserService;
import org.socialnetworklabseven.service.Network;
import org.socialnetworklabseven.service.NewUserService;

import java.io.IOException;

public class SignInController {
    @FXML
    private TextField emailField;
    @FXML
    private TextField firstNameField;
    @FXML
    private TextField lastNameField;
    @FXML
    private PasswordField passwordField;

    private NewUserService newUserService;
    private Network network;
    private PendingRequestsRepository pendingRequestsRepository;
    private MessageDataBaseRepository messageDataBaseRepository;

    public void setMessageDataBaseRepository(MessageDataBaseRepository messageDataBaseRepository) {
        this.messageDataBaseRepository = messageDataBaseRepository;
    }
    @FXML
    public void handleSignIn() {
        String email = emailField.getText();
        String firstName = firstNameField.getText();
        String lastName = lastNameField.getText();
        String password = passwordField.getText();
        try{
            User newUser = new User(firstName, lastName);
            System.out.println(newUser);
            newUser.setId(email);
            newUser.setPassword(password);
            NewUserService newUserService = new NewUserService(network, newUser);
            newUserService.registerUser();
            System.out.println("Utilizator înregistrat cu succes: " + email);
            LoggedUserService loggedUserService = new LoggedUserService(network,newUser,pendingRequestsRepository);
            loggedUserService.setMessageRepo(messageDataBaseRepository);
            try{
                FXMLLoader loader = new FXMLLoader(getClass().getResource("/userProfile.fxml"));
                Scene scene = new Scene(loader.load());
                UserProfileController userProfileController = loader.getController();
                userProfileController.setLoggedUserService(loggedUserService);
                Stage stage = new Stage();
                stage.setScene(scene);
                stage.setTitle("User Profile");
                stage.show();
                Stage currentStage = (Stage) emailField.getScene().getWindow();
                currentStage.close();

            }catch (IOException e){
                e.printStackTrace();
            }
        }catch (Exception e){
            showAlert("Error","The datas provided are wrong");
        }

    }

    public void setSocialNetwork(NewUserService socialNetwork) {
        this.newUserService = socialNetwork;
    }

    public void setNetwork(Network network) {
        this.network = network;
    }

    public void setPendingRequestsRepository(PendingRequestsRepository pendingRequestsRepository) {
        this.pendingRequestsRepository = pendingRequestsRepository;
    }
    private void showAlert(String title, String content) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(content);
        alert.showAndWait();
    }
}
