package ro.mpp.controllers;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.VBox;
import javafx.stage.FileChooser;
import javafx.stage.Stage;
import ro.mpp.*;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class EngineerController implements Observer {

    @FXML
    private GridPane missionGridPane;
    @FXML private Button              logoutButton;
    private final ObservableList<Assigned> assignments = FXCollections.observableArrayList();

    private Service service;
    private User loggedEngineer;

    public void setService(Service service) throws Exception {
        this.service = service;
        loadAssignments();
    }

    public void setUser(User engineer) {
        this.loggedEngineer = engineer;
    }

    private void loadAssignments() throws Exception {
        List<Assigned> list = service.getAssignmentsForUser(loggedEngineer.getId());

        assignments.setAll(
                list.stream()
                        .filter(a -> a.getUploadFileName() == null && !a.getMission().isFinished())
                        .toList()
        );
        populateMissionGrid();
    }

    private void populateMissionGrid() {
        missionGridPane.getChildren().clear();
        int col = 0, row = 0;
        for (Assigned ass : assignments) {
            VBox card = createMissionCard(ass);
            missionGridPane.add(card, col, row);
            if (++col == 3) { col = 0; row++; }
        }
    }

    private VBox createMissionCard(Assigned ass) {
        Mission m = ass.getMission();

        VBox card = new VBox(10);
        card.getStyleClass().add("mission-card");

        Label lblDesc = new Label("Mission: " + m.getDescription());
        Button btnFinish = new Button("Finish Mission");
        btnFinish.setOnAction(e -> showUploadWindow(ass));

        card.getChildren().addAll(lblDesc, btnFinish);
        return card;
    }

    private void showUploadWindow(Assigned ass) {
        FileChooser fc = new FileChooser();
        fc.setTitle("Upload File for Mission");
        File file = fc.showOpenDialog(missionGridPane.getScene().getWindow());

        if (file != null) {
            try {
                service.uploadFileForAssignment(ass.getId(), file.getAbsolutePath());

                showAlert("Success", "File uploaded successfully!");
                loadAssignments();

            } catch (Exception ex) {
                showAlert("Upload Failed", ex.getMessage());
            }
        }
    }

    @FXML
    private void handleLogout() {
        try {
            Stage primaryStage = new Stage();
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/login.fxml"));
            AnchorPane root = loader.load();
            LogInController loginController = loader.getController();
            loginController.initService(service);
            loginController.setPrimaryStage(primaryStage);
            Stage stage = new Stage();
            stage.setScene(new Scene(root));
            stage.setTitle("Login");
            stage.show();
            Stage currentStage = (Stage) logoutButton.getScene().getWindow();
            currentStage.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void showAlert(String title, String message) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }

    @Override
    public void assignmentUpdated(Assigned updatedAssignment) throws Exception {
        Platform.runLater(() -> {
            assignments.removeIf(a -> a.getId().equals(updatedAssignment.getId()));
            populateMissionGrid();
            showAlert("Success", "Your upload was received!");
        });
    }
}
