package map.repository.database;



import map.domain.User;
import map.domain.validators.Validator;
import map.repository.Repository;


import java.sql.*;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class UserDataBaseRepository implements Repository<String, User> {
    private String url;
    private String username;
    private String password;
    private Validator<User> validator;

    public UserDataBaseRepository(String url, String username, String password, Validator<User> validator) {
        this.url = url;
        this.username = username;
        this.password = password;
        this.validator = validator;
    }


    @Override
    public Optional<User> findOne(String email) {
        String query = "SELECT * FROM users WHERE email = ?";
        User user = null;
        try (Connection connection = DriverManager.getConnection("jdbc:postgresql://localhost:5432/SocialNetwork", "postgres", "teiubesctati17");
             PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, email);
            ResultSet resultSet = statement.executeQuery();

            if (resultSet.next()) {
                String firstName = resultSet.getString("name");
                String lastName = resultSet.getString("surname");
                user = new User(firstName, lastName);
                user.setId(email);
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return Optional.ofNullable(user); // Return an Optional user, can be empty if not found
    }

    @Override
    public Iterable<User> findAll() {
        Set<User> users = new HashSet<>();
        try (Connection connection = DriverManager.getConnection(url, username, password);
            PreparedStatement statement = connection.prepareStatement("SELECT * from users");
            ResultSet resultSet = statement.executeQuery()) {
            while (resultSet.next()) {
               String email = resultSet.getString("email");
                String firstName = resultSet.getString("name");
                String lastName = resultSet.getString("surname");
                User utilizator = new User(firstName, lastName);
                utilizator.setId(email);
                users.add(utilizator);
            }
            return users;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return users;
    }

    @Override
    public Optional<User> save(User entity) {
        int rez = -1;
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("INSERT INTO users (email, name, surname) VALUES (?,?, ?)");
             ) {
            statement.setString(1,entity.getId());
            statement.setString(2, entity.getFirstName());
            statement.setString(3, entity.getLastName());
            rez = statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        if (rez > 0)
            return Optional.empty();
        else 
            return Optional.ofNullable(entity);
    }

    @Override
    public Optional<User> delete(String email) {
        String query = "DELETE FROM users WHERE email = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(query);){
             statement.setString(1, email);
             statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        User user = null;
        for( User u : findAll() ) {
            if(u.getId().equals(email)) {
                user = u;
            }
        }
        return Optional.ofNullable(user);
    }

    @Override
    public Optional<User> update(User entity) {
        return null;
    }


}
