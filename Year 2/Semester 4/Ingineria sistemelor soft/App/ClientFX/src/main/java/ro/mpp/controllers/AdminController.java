package ro.mpp.controllers;

import javafx.application.Platform;
import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
import ro.mpp.*;

import java.io.IOException;
import java.net.URL;
import java.time.LocalDate;
import java.util.List;
import java.util.Optional;
import java.util.ResourceBundle;

public class AdminController implements Observer {

    /* ───  FXML ─────────────────────────────────────────────── */
    @FXML private TableView<User>     engineerTable;
    @FXML private TableView<Mission>  missionTable;
    @FXML private TableView<Assigned> assignmentTable;
    @FXML private ComboBox<User>      engineerCombo;
    @FXML private ComboBox<Mission>   missionCombo;
    @FXML private Button              logoutButton;


    private Service service;
    private User    loggedAdmin;

    private final ObservableList<User>     engineers   = FXCollections.observableArrayList();
    private final ObservableList<Mission>  missions    = FXCollections.observableArrayList();
    private final ObservableList<Assigned> assignments = FXCollections.observableArrayList();

    public void setService(Service service) throws Exception {
        this.service = service;
        TableColumn<User,String> colEmail = new TableColumn<>("Email");
        colEmail.setCellValueFactory(c ->
                new ReadOnlyStringWrapper(c.getValue().getEmail()));
        TableColumn<User,String> colName  = new TableColumn<>("Name");
        colName.setCellValueFactory(c ->
                new ReadOnlyStringWrapper(c.getValue().getName()));
        engineerTable.getColumns().setAll(colEmail, colName);

        TableColumn<Mission,String> colDesc = new TableColumn<>("Description");
        colDesc.setCellValueFactory(c ->
                new ReadOnlyStringWrapper(c.getValue().getDescription()));
        TableColumn<Mission,LocalDate> colDeadline = new TableColumn<>("Deadline");
        colDeadline.setCellValueFactory(new PropertyValueFactory<>("deadline"));
        missionTable.getColumns().setAll(colDesc, colDeadline);

        // ── Assignments ───────────────────
        TableColumn<Assigned,String> colUser = new TableColumn<>("Engineer");
        colUser.setCellValueFactory(c ->
                new ReadOnlyStringWrapper(c.getValue().getUser().getEmail()));
        TableColumn<Assigned,String> colMission = new TableColumn<>("Mission");
        colMission.setCellValueFactory(c ->
                new ReadOnlyStringWrapper(c.getValue().getMission().getDescription()));
        assignmentTable.getColumns().setAll(colUser, colMission);
        loadEngineers();  loadMissions();  loadAssignments();
    }
    public void setUser(User admin) { this.loggedAdmin = admin; }

    private void loadEngineers() throws Exception {
        List<User> all = service.getAllUsers();
        engineers.setAll(all.stream().filter(u -> !u.isAdmin()).toList());
        engineerTable.setItems(engineers);
        engineerCombo.setItems(engineers);
    }
    private void loadMissions() throws Exception {
        missions.setAll(service.getAllMissions());
        missionTable.setItems(missions);
        missionCombo.setItems(missions);
    }
    private void loadAssignments() throws Exception {
        List<Assigned> all = service.getAllAssignments();
        List<Assigned> toValidate = all.stream()
                .filter(a -> a.getMission().isFinished())
                .filter(a -> !a.isValidated())
                .toList();
        assignments.setAll(toValidate);
        assignmentTable.setItems(assignments);
    }

    @FXML
    private void handleAssignMission() {
        User    u = engineerCombo.getValue();
        Mission m = missionCombo.getValue();
        if (u == null || m == null) { alert("Assign Error", "Select engineer & mission"); return; }
        try {
            service.assignMissionToUser(new Assigned(u, m));
            alert("Success", "Mission assigned!");
            loadAssignments();
        } catch (Exception e) { alert("Error", e.getMessage()); }
    }

    @FXML
    private void handleValidateAssignment() {
        Assigned sel = assignmentTable.getSelectionModel().getSelectedItem();
        if (sel == null) { alert("Validation Error", "Select an assignment"); return; }
        try {
            service.validateAssignment(sel.getId());
            alert("Success", "Assignment validated");
            loadAssignments();
        } catch (Exception e) { alert("Error", e.getMessage()); }
    }

    @FXML
    private void openAddMissionDialog() {
        Dialog<Mission> dialog = new Dialog<>();
        dialog.setTitle("Add Mission");

        DatePicker dpDeadline  = new DatePicker();
        TextArea   taDesc      = new TextArea();
        taDesc.setPrefRowCount(3);

        GridPane grid = new GridPane();
        grid.setVgap(10); grid.setHgap(10);
        grid.addRow(0, new Label("Deadline:"),    dpDeadline);
        grid.addRow(1, new Label("Description:"), taDesc);
        dialog.getDialogPane().setContent(grid);

        ButtonType addBtn = new ButtonType("Add", ButtonBar.ButtonData.OK_DONE);
        dialog.getDialogPane().getButtonTypes().addAll(addBtn, ButtonType.CANCEL);

        dialog.setResultConverter(btn -> btn == addBtn
                ? new Mission(dpDeadline.getValue(), taDesc.getText(), false)
                : null);

        Optional<Mission> result = dialog.showAndWait();
        result.ifPresent(m -> {
            try {
                service.addMission(m);
                alert("Success", "Mission added");
                loadMissions();
            } catch (Exception ex) { alert("Error", ex.getMessage()); }
        });
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


    private void alert(String title, String message) {
        Alert a = new Alert(Alert.AlertType.INFORMATION, message);
        a.setTitle(title);
        a.setHeaderText(null);
        a.initOwner(engineerTable.getScene().getWindow());
        a.showAndWait();
    }

    @Override
    public void assignmentUpdated(Assigned updated) throws Exception {
        Platform.runLater(() -> {
            try {
                loadAssignments();
            } catch (Exception e) {
                e.printStackTrace();
            }
        });
    }
}
