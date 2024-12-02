package org.socialnetworklabseven;

import  org.socialnetworklabseven.domain.Friendship;
import  org.socialnetworklabseven.domain.Tuple;
import  org.socialnetworklabseven.domain.User;
import org.socialnetworklabseven.domain.validators.FriendshipValidator;
import  org.socialnetworklabseven.domain.validators.UserValidator;
import  org.socialnetworklabseven.repository.Repository;
import  org.socialnetworklabseven.repository.database.FriendshipDataBaseRepository;
import  org.socialnetworklabseven.repository.database.UserDataBaseRepository;
import  org.socialnetworklabseven.repository.memory.InMemoryRepository;
import  org.socialnetworklabseven.service.Network;
import  org.socialnetworklabseven.service.ServiceFriendships;
import  org.socialnetworklabseven.service.ServiceUsers;
import  org.socialnetworklabseven.ui.Console;

import java.util.Scanner;

// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    private static void start(){
    }
    public static void main(String[] args) {
        start();
    }
}