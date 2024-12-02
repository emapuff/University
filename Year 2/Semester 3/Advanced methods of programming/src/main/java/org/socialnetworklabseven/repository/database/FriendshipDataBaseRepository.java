package org.socialnetworklabseven.repository.database;
import  org.socialnetworklabseven.domain.Friendship;
import  org.socialnetworklabseven.domain.Tuple;
import  org.socialnetworklabseven.domain.User;
import org.socialnetworklabseven.domain.pagining.Page;
import org.socialnetworklabseven.domain.pagining.Pageable;
import  org.socialnetworklabseven.domain.validators.FriendshipValidator;
import org.socialnetworklabseven.repository.PagingRepository;
import java.sql.*;
import java.time.LocalDateTime;
import java.time.ZoneOffset;

import java.util.*;

public class FriendshipDataBaseRepository implements PagingRepository<Tuple<User, User>, Friendship> {

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
            statement.setTimestamp(3, Timestamp.valueOf(entity.getDate()));
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

    //private Pair<String, List<Object>> toSql()

    private int count(String email) throws SQLException {
        String query = "SELECT COUNT(*) as count FROM friendships WHERE first_email = ? OR second_email = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setString(1, email);
            statement.setString(2, email);

            try (ResultSet result = statement.executeQuery()) {
                if (result.next()) {
                    return result.getInt("count");
                }
            }
        }
        return 0;
    }

    private List<Friendship> findAllOnPagePrivate(String email, Pageable pageable) throws SQLException{
        List<Friendship> friendshipsUsers = new ArrayList<>();
        String query = "SELECT * FROM friendships WHERE first_email = ? OR second_email = ? limit ? offset ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
        PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, email);
            statement.setString(2, email);
            statement.setInt(3, pageable.getPageSize());
            statement.setInt(4,pageable.getPageSize() * pageable.getPageNumber());
            try(ResultSet resultSet = statement.executeQuery()) {
                while (resultSet.next()) {
                    String firstEmail = resultSet.getString("first_email");
                    String secondEmail = resultSet.getString("second_email");
                    Timestamp date = resultSet.getTimestamp("friendship_date");
                    LocalDateTime friendsFrom = LocalDateTime.ofInstant(date.toInstant(), ZoneOffset.ofHours(0));
                    User u1 = users.findOne(firstEmail).orElseThrow(()
                            -> new RuntimeException("User not found for email: " + firstEmail));
                    User u2 = users.findOne(secondEmail).orElseThrow(()
                            -> new RuntimeException("User not found for email: " + secondEmail));
                    User userMin = (firstEmail.compareTo(secondEmail) < 0) ? u1 : u2;
                    User userMax = (firstEmail.compareTo(secondEmail) < 0) ? u2 : u1;
                    Friendship friendship = new Friendship(userMin, userMax);
                    Tuple<User, User> tuple = new Tuple<>(userMin, userMax);
                    friendship.setId(tuple);
                    friendship.setDate(friendsFrom);
                    friendshipsUsers.add(friendship);
                }
            }
        }
        return friendshipsUsers;
    }

    @Override
    public Page<Friendship> findAllOnPage(String email, Pageable pageable) {
        try{
            List<Friendship> friendshipsUsers;
            int totalElements = count(email);
            if(totalElements == 0) {
                friendshipsUsers = new ArrayList<>();
            }else{
                friendshipsUsers = findAllOnPagePrivate(email, pageable);
            }
            return new Page<>(friendshipsUsers, totalElements);
        }catch (SQLException e){
            throw new RuntimeException("Eroare la baza de date la paginare");
        }
    }
}
