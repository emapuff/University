package org.socialnetworklabseven.repository.database;

import org.socialnetworklabseven.domain.Tuple;
import org.socialnetworklabseven.domain.User;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class PendingRequestsRepository {
    private String url;
    private String username;
    private String password;
    private UserDataBaseRepository usersData;

    public PendingRequestsRepository(String url, String username, String password, UserDataBaseRepository usersData) {
        this.url = url;
        this.username = username;
        this.password = password;
        this.usersData = usersData;
    }

    public void save(User userFrom, User userTo){
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("INSERT INTO pendings (from_user,to_user,date) VALUES (?,?,?)");
        ){
            statement.setString(1,userFrom.getId());
            statement.setString(2,userTo.getId());
            statement.setTimestamp(3, Timestamp.valueOf(LocalDateTime.now()));
            statement.executeUpdate();
        }catch (SQLException e){
            e.printStackTrace();
        }
    }

    public void delete(User userFrom, User userTo){
        String query = "DELETE FROM pendings WHERE from_user = ? AND to_user = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(query);){
            statement.setString(1, userFrom.getId());
            statement.setString(2, userTo.getId());
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public List<Tuple<User, LocalDateTime>> findAllForOneUser(User userFrom) throws SQLException {
        List<Tuple<User, LocalDateTime>> users = new ArrayList<>();
        String sql = "SELECT * FROM pendings WHERE \"to_user\" = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement stmt = connection.prepareStatement(sql)) {
            stmt.setString(1, userFrom.getId());

            try (ResultSet rs = stmt.executeQuery()) {
                while (rs.next()) {
                    String fromEmail = rs.getString("from_user");
                    String toEmail = rs.getString("to_user");
                    LocalDateTime date = rs.getTimestamp("date").toLocalDateTime();
                    Optional<User> userOptional = usersData.findOne(fromEmail);
                    if (userOptional.isPresent()) {
                        User user = userOptional.get();
                        users.add(new Tuple<>(user, date));
                    }
                }
            }catch (SQLException e){
                e.printStackTrace();
            }
        }catch (SQLException e){
            e.printStackTrace();
        }
        return users;
    }


}
