package org.socialnetworklabseven;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;
import org.socialnetworklabseven.domain.Tuple;
import org.socialnetworklabseven.domain.User;
import org.socialnetworklabseven.service.LoggedUserService;
import org.socialnetworklabseven.ui.MessageBox;

import java.sql.SQLException;
import java.time.LocalDateTime;

public class UserProfileController {
    @FXML
    private Label userNameLabel;

    @FXML
    private Label userEmailLabel;

    @FXML
    private TableView<User> friendsTable;

    @FXML
    private TableColumn<User, String> friendNameColumn;

    @FXML
    private TableColumn<User, String> friendEmailColumn;

    @FXML
    private ListView<Tuple<User, LocalDateTime>> notificationsList;

    @FXML
    private TableView<User> otherUsersTable;

    @FXML
    private TableColumn<User, String> otherUserNameColumn;

    @FXML
    private TableColumn<User, String> otherUserEmailColumn;

    @FXML
    private TableView<User> messagesTable;

    @FXML
    private TableColumn<User, String> messageNameColumn;

    @FXML
    private Button deleteFriendButton;

    @FXML
    private Button addFriendButton;

    private LoggedUserService loggedUserService;

    public void setLoggedUserService(LoggedUserService loggedUserService) {
        this.loggedUserService = loggedUserService;
        loadUserData();
    }
    @FXML
    private Label noPendingRequestsLabel;

    private void loadUserData() {
        User loggedUser = loggedUserService.getLoggedUser();
        userNameLabel.setText(loggedUser.getFirstName() + " " + loggedUser.getLastName());
        userEmailLabel.setText(loggedUser.getId());

        ObservableList<User> friends = FXCollections.observableArrayList(loggedUserService.getFriendships());
        friendNameColumn.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        friendEmailColumn.setCellValueFactory(new PropertyValueFactory<>("id"));
        friendsTable.setItems(friends);

        try {
            ObservableList<Tuple<User, LocalDateTime>> pendingRequests = FXCollections.observableArrayList(loggedUserService.getPendingRequests());
            if (pendingRequests == null || pendingRequests.isEmpty()) {
                notificationsList.setVisible(false);
                noPendingRequestsLabel.setVisible(true);
            } else {
                notificationsList.setVisible(true);
                noPendingRequestsLabel.setVisible(false);
                notificationsList.setItems(pendingRequests);
            }
        } catch (SQLException e) {
            showAlert("Database error", "Failed to load pending requests.");
        }

        ObservableList<User> otherUsers = FXCollections.observableArrayList(loggedUserService.getOtherUsers());
        otherUserNameColumn.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        otherUserEmailColumn.setCellValueFactory(new PropertyValueFactory<>("id"));
        otherUsersTable.setItems(otherUsers);

//        ObservableList<User> messageUsers = FXCollections.observableArrayList(loggedUserService.getUsersThatSentMessages());
//        messageNameColumn.setCellValueFactory(new PropertyValueFactory<>("firstName"));
//        messagesTable.setItems(messageUsers);
    }

    @FXML
    private void handleDeleteFriend() {
        User selectedFriend = friendsTable.getSelectionModel().getSelectedItem();
        if (selectedFriend == null) {
            showAlert("No Selection", "Please select a friend to delete.");
            return;
        }

            loggedUserService.deleteFriendship(selectedFriend);
            showAlert("Success", "Friend deleted successfully.");
            loadUserData();

    }

    @FXML
    private void handleAcceptRequest() {
        Tuple<User, LocalDateTime> selectedRequest = notificationsList.getSelectionModel().getSelectedItem();
        if (selectedRequest == null) {
            showAlert("No Selection", "Please select a pending request to accept.");
            return;
        }
            loggedUserService.acceptFriendRequest(selectedRequest.getFirst());
            showAlert("Success", "Friend request accepted.");
            loadUserData(); // Refresh the data
    }

    @FXML
    private void handleAddFriend() {
        User selectedUser = otherUsersTable.getSelectionModel().getSelectedItem();
        if (selectedUser == null) {
            showAlert("No Selection", "Please select a user to add as a friend.");
            return;
        }
            loggedUserService.pendFriendRequest(selectedUser);
            showAlert("Success", "Friend request sent successfully.");
            loadUserData();
    }

    private void showAlert(String title, String content) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(content);
        alert.showAndWait();
    }

    public void handleOpenMessageBox() {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/message-box.fxml"));
            Parent root = loader.load();
            User friend = friendsTable.getSelectionModel().getSelectedItem();
            if (friend == null) {
                showAlert("No Selection", "Please select a friend to add as a message.");
            }else{
                MessageBox controller = loader.getController();
                controller.setNetwork(loggedUserService);
                controller.setApp(loggedUserService.getLoggedUser(),friend);

                Stage stage = new Stage();
                stage.setTitle("Message Box");
                stage.setScene(new Scene(root));
                stage.show();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
