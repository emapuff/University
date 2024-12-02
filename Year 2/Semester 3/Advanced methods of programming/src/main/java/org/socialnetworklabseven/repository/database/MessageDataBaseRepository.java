package org.socialnetworklabseven.repository.database;
import org.socialnetworklabseven.domain.MessageDTO;
import org.socialnetworklabseven.domain.Tuple;
import org.socialnetworklabseven.domain.User;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
public class MessageDataBaseRepository {
    private String url;
    private String username;
    private String password;
    private UserDataBaseRepository users;

    public MessageDataBaseRepository(String url, String username, String password,UserDataBaseRepository users) {
        this.url = url;
        this.username = username;
        this.password = password;
        this.users = users;
    }

    public void save(User userFrom, User userTo, String message) {
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("INSERT INTO messages (from_user,to_user,message,date) VALUES (?,?,?,?)");
        ){
            statement.setString(1,userFrom.getId());
            statement.setString(2,userTo.getId());
            statement.setString(3,message);
            statement.setTimestamp(4, Timestamp.valueOf(LocalDateTime.now()));
            statement.executeUpdate();
        }catch (SQLException e){
            e.getMessage();
        }
    }

    public void delete(User userFrom, User userTo) {
        String query = "DELETE FROM messages WHERE from_user = ? AND to_user = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(query);){
            statement.setString(1, userFrom.getId());
            statement.setString(2, userTo.getId());
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public List<MessageDTO> findAllMessages(User userFrom, User userTo) {
        List<MessageDTO> messages = new ArrayList<>();
        String sql = """
                SELECT from_user, to_user, message, date 
                FROM messages
                WHERE (from_user = ? AND to_user = ?)
                   OR (from_user = ? AND to_user = ?)
                ORDER BY date ASC
                """;

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement stmt = connection.prepareStatement(sql);) {
            stmt.setString(1, userFrom.getId());
            stmt.setString(2, userTo.getId());
            stmt.setString(3, userTo.getId());
            stmt.setString(4, userFrom.getId());
            ResultSet rs = stmt.executeQuery();

            while (rs.next()) {
                String fromUserId = rs.getString("from_user");
                String toUserId = rs.getString("to_user");
                String messageText = rs.getString("message");
                LocalDateTime dateReceived = rs.getTimestamp("date").toLocalDateTime();

//                // Determine logged_user and friend_user
//                User loggedUser = (fromUserId == userFrom.getId()) ? userFrom : userTo;
//                User friendUser = (fromUserId == userFrom.getId()) ? userTo : userFrom;

                // Create MessageDTO
                MessageDTO messageDTO = new MessageDTO(
                        users.findOne(toUserId).get(),
                        users.findOne(fromUserId).get(),
                        dateReceived,
                        Optional.ofNullable(messageText)
                );
                System.out.println(messageDTO);
                messages.add(messageDTO);
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return messages;
    }

    public List<User> findMessagedUsers(User userFrom) {
        List<User> usersList = new ArrayList<>();
        String sql = """
                SELECT from_user
                FROM messages
                WHERE to_user = ?
                ORDER BY date ASC
                """;

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement stmt = connection.prepareStatement(sql);) {
            stmt.setString(1, userFrom.getId());
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                String fromUserId = rs.getString("from_user");
                Optional<User> userOptional = users.findOne(fromUserId);
                if (userOptional.isPresent()) {
                    User user = userOptional.get();
                    usersList.add(user);
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return usersList;
    }
}
