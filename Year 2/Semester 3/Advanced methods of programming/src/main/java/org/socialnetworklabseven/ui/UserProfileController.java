package org.socialnetworklabseven.ui;

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
import org.socialnetworklabseven.domain.pagining.Page;
import org.socialnetworklabseven.domain.pagining.Pageable;
import org.socialnetworklabseven.service.LoggedUserService;

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

    @FXML
    private Button buttonNext;

    @FXML
    private Button buttonPrevious;

    @FXML
    private Label labelPage;

    private int pageSize = 5;
    private int currentPage = 0;
    private int totalNumberOfElements = 0;

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

        updateFriendsTable();

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

    private void updateFriendsTable() {
        Pageable pageable = new Pageable(currentPage, pageSize);
        System.out.println(pageable.getPageNumber());
        System.out.println(pageable.getPageSize());
        Page<User> userPage = loggedUserService.getPageUser(pageable);

        totalNumberOfElements = userPage.getTotalNumberOfElements();

        ObservableList<User> friends = FXCollections.observableArrayList(userPage.getContent());
        friendNameColumn.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        friendEmailColumn.setCellValueFactory(new PropertyValueFactory<>("id"));
        friendsTable.setItems(friends);

        labelPage.setText("Page: " + (currentPage + 1) + " / " + ((totalNumberOfElements + pageSize - 1) / pageSize));

        buttonPrevious.setDisable(currentPage == 0);
        buttonNext.setDisable((currentPage + 1) * pageSize >= totalNumberOfElements);
    }

    @FXML
    private void handleNextPage() {
        if ((currentPage + 1) * pageSize < totalNumberOfElements) {
            currentPage++;
            updateFriendsTable();
        }
    }

    @FXML
    private void handlePreviousPage() {
        if (currentPage > 0) {
            currentPage--;
            updateFriendsTable();
        }
    }
}
