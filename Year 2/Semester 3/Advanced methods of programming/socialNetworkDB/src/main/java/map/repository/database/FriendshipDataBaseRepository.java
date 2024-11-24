package map.repository.database;

import map.domain.Friendship;
import map.domain.Tuple;
import map.domain.User;
import map.domain.validators.FriendshipValidator;
import map.domain.validators.ValidationException;
import map.domain.validators.Validator;
import map.repository.Repository;
import map.repository.database.UserDataBaseRepository;

import java.sql.*;
import java.time.LocalDateTime;
import java.time.ZoneOffset;

import java.util.HashMap;
import java.util.Map;
import java.util.Objects;
import java.util.Optional;

public class FriendshipDataBaseRepository implements Repository<Tuple<User, User>, Friendship> {

    FriendshipValidator friendshipValidator;
    private String url;
    private String username;
    private String password;
    private UserDataBaseRepository users;

    public FriendshipDataBaseRepository(String url, String user, String password, FriendshipValidator friendshipValidator,UserDataBaseRepository users) {
        this.friendshipValidator = friendshipValidator;
        this.url = url;
        this.username = user;
        this.password = password;
        this.users = users;
    }

    @Override
    public Optional<Friendship> findOne(Tuple<User, User> userTuple) {
        return Optional.empty();
    }

    @Override
    public Iterable<Friendship> findAll() {
        Map<Tuple<User,User>, Friendship> friendships = new HashMap<>();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("SELECT * FROM friendships");
             ResultSet resultSet = statement.executeQuery()) {
                while (resultSet.next()) {
                    String email1 = resultSet.getString("first_email");
                    String email2 = resultSet.getString("second_email");
                    Timestamp date = resultSet.getTimestamp("friendship_date");
                    LocalDateTime friendsFrom = LocalDateTime.ofInstant(date.toInstant(), ZoneOffset.ofHours(0));
                    User u1 = users.findOne(email1).orElseThrow(()
                            -> new RuntimeException("User not found for email: " + email1));
                    User u2 = users.findOne(email2).orElseThrow(()
                            -> new RuntimeException("User not found for email: " + email2));
                    User userMin = (email1.compareTo(email2) < 0) ? u1 : u2;
                    User userMax = (email1.compareTo(email2) < 0) ? u2 : u1;
                    Friendship friendship = new Friendship(userMin, userMax);
                    Tuple<User, User> tuple = new Tuple<>(userMin, userMax);
                    friendship.setId(tuple);
                    friendship.setDate(friendsFrom);
                    friendships.put(tuple, friendship);
                }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return friendships.values();
    }

    @Override
    public Optional<Friendship> save(Friendship entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Friendship can't be null!");
        }
        String query = "INSERT INTO friendships(\"first_email\", \"second_email\", \"friendship_date\") VALUES (?,?,?)";

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(query);) {
            statement.setString(1, entity.getU1().getId());
            statement.setString(2, entity.getU2().getId());
            statement.setTimestamp(3, java.sql.Timestamp.valueOf(entity.getDate()));
            statement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return Optional.of(entity);
    }

    @Override
    public Optional<Friendship> delete(Tuple<User, User> tuple) {
        String query = "DELETE FROM friendships WHERE first_email = ? AND second_email = ?";
        Friendship friendshipToDelete = null;

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, tuple.getFirst().getId());
            statement.setString(2, tuple.getSecond().getId());

            int affectedRows = statement.executeUpdate();
            if (affectedRows > 0) {
                for (Friendship friendship : findAll()) {
                    if (Objects.equals(friendship.getId(), tuple)) {
                        friendshipToDelete = friendship;
                    }
                }
            } else {
                System.out.println("No friendship found to delete for " + tuple);
            }
        } catch (SQLException e) {
            e.printStackTrace();
            throw new RuntimeException(e);
        }

        return Optional.ofNullable(friendshipToDelete);
    }


    @Override
    public Optional<Friendship> update(Friendship entity) {
        return Optional.empty();
    }
}