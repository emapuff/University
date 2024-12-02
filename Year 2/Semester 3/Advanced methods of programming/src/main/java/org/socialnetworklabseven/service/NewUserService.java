package org.socialnetworklabseven.service;

import org.socialnetworklabseven.domain.User;

public class NewUserService {
    private final Network network;
    private final User new_user;

    public NewUserService(Network network, User new_user) {
        this.network = network;
        this.new_user = new_user;
    }

    public void registerUser() {
        System.out.println("Registering new user"+new_user);
        network.addUser(new_user);
        System.out.println("Registered new user"+new_user);
    }
}
