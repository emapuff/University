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
    private void handleLogin() {
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
            User probe = service.login(email, password, new ClientObserver());
            // imediat logout ca să nu rămână observer-ul dummy
            service.logout(probe, new ClientObserver());

            boolean isAdmin = probe.isAdmin();
            String fxml = isAdmin ? "/admin.fxml" : "/engineer.fxml";

            FXMLLoader loader = new FXMLLoader(getClass().getResource(fxml));
            Parent root = loader.load();

            if (isAdmin) {
                AdminController ctrl = loader.getController();
                User logged = service.login(email, password, ctrl);
                ctrl.setUser(logged);
                ctrl.setService(service);
            } else {
                EngineerController ctrl = loader.getController();
                User logged = service.login(email, password, ctrl);
                ctrl.setUser(logged);
                ctrl.setService(service);
            }

            Stage loginStage = (Stage) emailField.getScene().getWindow();
            loginStage.close();

            Stage dash = new Stage();
            dash.setTitle("Welcome, " + email);
            dash.setScene(new Scene(root));
            dash.show();

        } catch (Exception e) {
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


    private static class ClientObserver implements Observer {
        @Override
        public void assignmentUpdated(ro.mpp.Assigned updatedAssignment) {
            System.out.println("[CLIENT] Assignment updated: " + updatedAssignment);

        }
    }
}
