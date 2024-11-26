package org.socialnetworklabseven.ui;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.ListCell;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;
import javafx.scene.text.TextFlow;
import org.socialnetworklabseven.domain.MessageDTO;
import org.socialnetworklabseven.domain.User;
import org.socialnetworklabseven.service.LoggedUserService;
import java.util.List;

public class MessageBox {

    @FXML
    public ListView<MessageDTO> conversationList;

    @FXML
    public TextField messageField;
    @FXML
    public Label conversationName;
    @FXML
    public Label selectedReplyMessageLable;
    @FXML
    public HBox replyBox;

    private MessageDTO selectedMessageForReply;

    private User user;
    private User friend;

    private LoggedUserService network;

    public void setApp(User user, User friend) {
        this.user = user;
        this.friend = friend;
        conversationName.setText(friend.getFirstName() + " " + friend.getLastName());
        loadConversation();
    }

    public void setNetwork(LoggedUserService network) {
        this.network = network;
    }

    private void loadConversation() {
        List<MessageDTO> messages = network.getListMessages(this.user, this.friend);
        ObservableList<MessageDTO> friendsList = FXCollections.observableArrayList();
        friendsList.setAll(messages);

        conversationList.setItems(friendsList);
        conversationList.setCellFactory(param -> new ListCell<>() {
            @Override
            protected void updateItem(MessageDTO message, boolean empty) {
                super.updateItem(message, empty);
                if (empty || user == null) {
                    setGraphic(null);
                } else {
                    VBox messageBox = new VBox(5);

// Create the message text
                    Text messageText = new Text(message.getMessage().orElse(""));
                    messageText.setStyle(!message.getFriend_user().getId().equals(friend.getId())
                            ?"-fx-fill: #F8F0E3;"
                            : "-fx-fill: black;");

// Wrap text inside a TextFlow
                    TextFlow messageTextFlow = new TextFlow(messageText);
                    messageTextFlow.setStyle("-fx-background-color: " +
                            (message.getFriend_user().getId().equals(friend.getId()) ? "#F8F0E3;" : "#800020;") +
                            "-fx-padding: 10; -fx-background-radius: 10;");
                    messageTextFlow.setMaxWidth(300);
                    messageTextFlow.setPrefWidth(TextFlow.USE_COMPUTED_SIZE);

                    messageBox.getChildren().add(messageTextFlow);

// Create the HBox container
                    HBox container = new HBox();
                    container.getChildren().add(messageBox);

// Determine alignment and style
                    if (message.getFriend_user().getId().equals(friend.getId())) {
                        // Message from the friend (left-aligned, cream background)
                        container.setStyle("-fx-alignment: CENTER-LEFT; -fx-padding: 10;");
                    } else {
                        // Message from the current user (right-aligned, burgundy background)
                        container.setStyle("-fx-alignment: CENTER-RIGHT; -fx-padding: 10;");
                    }
// Set the container as the graphic
                    setGraphic(container);

                }
            }
        });
        conversationList.setOnMouseClicked(event -> {
            MessageDTO selectedMessage = conversationList.getSelectionModel().getSelectedItem();
            if (selectedMessage != null) {
                selectedMessageForReply = selectedMessage;
                replyBox.setVisible(true);
                selectedReplyMessageLable.setText("Reply to: [" + selectedMessage.getMessage() + "]");
                messageField.setPromptText("Reply to " + selectedMessage.getMessage());
            }
        });
    }

    public void onSendButtonClick(ActionEvent actionEvent) {
        try{
            String message = messageField.getText();
            network.sendMessage(friend,message);
            messageField.clear();
            //clearReply();
            loadConversation();
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }

    public void onClearReplyButtonClicked(ActionEvent actionEvent) {
        clearReply();
    }

    private void clearReply() {
        selectedMessageForReply = null;
        replyBox.setVisible(false);
        selectedReplyMessageLable.setText(null);
        messageField.setPromptText("Message");
    }
}

