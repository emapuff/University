package ro.mpp.controllers;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import ro.mpp.Assigned;
import ro.mpp.Mission;
import ro.mpp.User;
import ro.mpp.Observer;
import ro.mpp.Service;

import java.util.List;

public class AdminController implements Observer {

    @FXML
    private TableView<User> engineerTable;

    @FXML
    private TableView<Mission> missionTable;

    @FXML
    private TableView<Assigned> assignmentTable;

    @FXML
    private ComboBox<User> engineerCombo;

    @FXML
    private ComboBox<Mission> missionCombo;

    private Service service;
    private User loggedAdmin;

    private final ObservableList<User> engineers = FXCollections.observableArrayList();
    private final ObservableList<Mission> missions = FXCollections.observableArrayList();
    private final ObservableList<Assigned> assignments = FXCollections.observableArrayList();

    public void setService(Service service) throws Exception {
        this.service = service;
        loadEngineers();
        loadMissions();
        loadAssignments();
    }

    public void setUser(User admin) {
        this.loggedAdmin = admin;
    }

    private void loadEngineers() throws Exception {
        List<User> allUsers = service.getAllUsers();
        engineers.setAll(allUsers.stream()
                .filter(u -> !u.isAdmin())
                .toList());
        engineerTable.setItems(engineers);
        engineerCombo.setItems(engineers);
    }

    private void loadMissions() throws Exception {
        missions.setAll(service.getAllMissions());
        missionTable.setItems(missions);
        missionCombo.setItems(missions);
    }

    private void loadAssignments() throws Exception {
        assignments.setAll(service.getUnvalidatedAssignments());
        assignmentTable.setItems(assignments);
    }

    @FXML
    private void handleAssignMission() {
        User selectedUser = engineerCombo.getValue();
        Mission selectedMission = missionCombo.getValue();

        if (selectedUser == null || selectedMission == null) {
            showAlert("Assign Error", "Select both an engineer and a mission.");
            return;
        }

        try {
            Assigned assigned = new Assigned(selectedUser, selectedMission);
            service.assignMissionToUser(assigned);
            showAlert("Success", "Mission assigned successfully.");
        } catch (Exception e) {
            showAlert("Error", e.getMessage());
        }
    }

    @FXML
    private void handleValidateAssignment() {
        Assigned selected = assignmentTable.getSelectionModel().getSelectedItem();
        if (selected == null) {
            showAlert("Validation Error", "Select an assignment to validate.");
            return;
        }

        try {
            service.validateAssignment(selected.getId());
            showAlert("Success", "Assignment validated.");
        } catch (Exception e) {
            showAlert("Error", e.getMessage());
        }
    }

    private void showAlert(String title, String msg) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(msg);
        alert.showAndWait();
    }

    @Override
    public void assignmentUpdated(Assigned updatedAssignment) throws Exception {
        // Optionally reload the assignments table
        loadAssignments();
    }
}
