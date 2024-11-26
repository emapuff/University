package org.socialnetworklabseven.service;

import org.socialnetworklabseven.domain.User;

public class BeginningService {
    private final Network network;
    public BeginningService(Network network) {
        this.network = network;
    }

    public Iterable<User> getUsers(){
        return network.getAllUsers();
    }

    public Boolean isUser(User user) {
        if (user == null || user.getId() == null || user.getPassword() == null) {
            return false;
        }
        for (User existingUser : network.getAllUsers()) {
            System.out.println(existingUser);
            if (existingUser.getId() != null && existingUser.getPassword() != null) {
                if (existingUser.getId().equals(user.getId()) &&
                        existingUser.getPassword().equals(user.getPassword())) {
                    return true;
                }
            }
        }
        return false;
    }

}
