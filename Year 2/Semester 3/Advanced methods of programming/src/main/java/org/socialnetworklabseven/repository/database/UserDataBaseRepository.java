package org.socialnetworklabseven.repository.database;



import  org.socialnetworklabseven.domain.User;
import  org.socialnetworklabseven.domain.validators.Validator;
import  org.socialnetworklabseven.repository.Repository;


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

        return Optional.ofNullable(user);
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
                String password = resultSet.getString("password");
                User utilizator = new User(firstName, lastName);
                utilizator.setId(email);
                utilizator.setPassword(password);
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
        try{
            validator.validate(entity);
            System.out.println(entity);
            try (Connection connection = DriverManager.getConnection(url, username, password);
                 PreparedStatement statement = connection.prepareStatement("INSERT INTO users (email, name, surname,password) VALUES (?,?, ?,?)");
            ) {
                statement.setString(1,entity.getId());
                statement.setString(2, entity.getFirstName());
                statement.setString(3, entity.getLastName());
                statement.setString(4, entity.getPassword());
                rez = statement.executeUpdate();
            } catch (SQLException e) {
                e.printStackTrace();
            }
            if (rez > 0)
                return Optional.empty();
            else
                return Optional.ofNullable(entity);
        }catch (Exception e) {
            System.out.println(e.getMessage());
            throw e;
        }

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
