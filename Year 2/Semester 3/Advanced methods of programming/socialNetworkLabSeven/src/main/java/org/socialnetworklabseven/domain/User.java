package org.socialnetworklabseven.domain;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class User extends Entity<String>{
    //alt enter -> generaza teste
    private String firstName;
    private String lastName;
    private final List<User> friends;
    private Boolean two_factor = false;
    private String password;

    public User(){
        this.friends = new ArrayList<>();
    }

    public User(String firstName, String lastName) {
        this.firstName = firstName;
        this.lastName = lastName;
        friends = new ArrayList<>();
    }

    public User(String firstName, String lastName,String password) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.password = password;
        friends = new ArrayList<>();
    }

    public Boolean getTwo_factor() {
        return two_factor;
    }

    public void setTwo_factor() {
        this.two_factor = true;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public List<User> getFriends() {
        return friends;
    }

    public void addFriend(User friend){
        friends.add(friend);
    }

    public void removeFriend(User friend){
        friends.remove(friend);
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    @Override
    public String toString() {
        return "Utilizator{" +
                "Email| " + getId() +
                " firstName| " + firstName + '\'' +
                " lastName | " + lastName + '\'' +
                "password| " + password + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof User)) return false;
        User that = (User) o;
        return getFirstName().equals(that.getFirstName()) &&
                getLastName().equals(that.getLastName());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getFirstName(), getLastName());
    }
}