package ro.mpp.controllers;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import ro.mpp.User;
import ro.mpp.Observer;
import ro.mpp.Service;

import java.awt.event.ActionEvent;

public class LogInController {

    @FXML
    private TextField emailField;

    @FXML
    private PasswordField passwordField;

    private Service service;
    private Stage primaryStage;

    public void setService(Service service, Stage stage) {
        this.service = service;
        this.primaryStage = stage;
    }


    public void setPrimaryStage(Stage stage) {
        this.primaryStage = stage;
    }

    public void initService(Service service) {
        this.service = service;
    }

    @FXML
    private void logIn(ActionEvent event) {
        if (service == null) {
            showAlert("Error", "Service not initialized!", Alert.AlertType.ERROR);
            return;
        }

        String email = emailField.getText().trim();
        String password = passwordField.getText().trim();

        if (email.isEmpty() || password.isEmpty()) {
            showAlert("Error", "Email and password cannot be empty!", Alert.AlertType.ERROR);
            return;
        }

        try {
            User loggedUser = service.login(email, password, new ClientObserver());

            FXMLLoader loader;
            Parent root;

            if (loggedUser.isAdmin()) {
                loader = new FXMLLoader(getClass().getResource("/admin.fxml"));
            } else {
                loader = new FXMLLoader(getClass().getResource("/engineer.fxml"));
            }

            root = loader.load();

            // Controllerul potrivit
            if (loggedUser.isAdmin()) {
                AdminController controller = loader.getController();
                controller.setService(service);
                controller.setUser(loggedUser);
            } else {
                EngineerController controller = loader.getController();
                controller.setService(service);
                controller.setUser(loggedUser);
            }

            Scene scene = new Scene(root);
            primaryStage.setScene(scene);
            primaryStage.setTitle("Welcome, " + loggedUser.getName());
            primaryStage.show();

        } catch (Exception e) {
            e.printStackTrace();
            showAlert("Login Failed", e.getMessage(), Alert.AlertType.ERROR);
        }
    }

    private void showAlert(String title, String message, Alert.AlertType type) {
        Alert alert = new Alert(type);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }

    // Inner class for observer implementation
    private static class ClientObserver implements Observer {
        @Override
        public void assignmentUpdated(ro.mpp.Assigned updatedAssignment) {
            System.out.println("[CLIENT] Assignment updated: " + updatedAssignment);

        }
    }
}
