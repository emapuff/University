package org.socialnetworklabseven;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.TextField;
import javafx.scene.control.PasswordField;
import javafx.stage.Stage;
import org.socialnetworklabseven.domain.User;
import org.socialnetworklabseven.repository.database.PendingRequestsRepository;
import org.socialnetworklabseven.service.BeginningService;
import org.socialnetworklabseven.service.LoggedUserService;
import org.socialnetworklabseven.service.Network;

import java.io.IOException;
import java.util.Optional;

public class LogInController {
    @FXML
    private TextField emailField;
    @FXML
    private PasswordField passwordField;

    private BeginningService beginningService;// Injectată în momentul inițializării.
    private Network network;
    private PendingRequestsRepository pendingRequestsRepository;

    @FXML
    public void handleLogIn() {
        String email = emailField.getText();
        String password = passwordField.getText();
        if (email.isEmpty() || password.isEmpty()) {
            showAlert("Validation Error", "Email and Password are required!");
            return;
        }

        User user = new User();
        user.setId(email);
        user.setPassword(password);
        System.out.println(user);
        if (beginningService.isUser(user)) {
            Optional<User> loggedUserOptional = network.getOne(email);
            LoggedUserService loggedUserService = new LoggedUserService(network, loggedUserOptional.get(),pendingRequestsRepository);
            showAlert("Success", "Welcome, " + user.getId() + "!");
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
        } else {
            showAlert("Login Failed", "Invalid email or password.");
        }
    }

    public void setNetwork(Network network) {
        this.network = network;
    }

    public void setBeginningService(BeginningService beginningService) {
        this.beginningService = beginningService;
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
