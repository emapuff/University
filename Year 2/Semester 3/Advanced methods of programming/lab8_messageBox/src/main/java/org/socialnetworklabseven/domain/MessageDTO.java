package org.socialnetworklabseven.domain;

import java.time.LocalDateTime;
import java.util.Optional;

public class MessageDTO {
    private User logged_user;
    private User friend_user;
    private LocalDateTime date_received;
    private Optional<String> message;

    public MessageDTO(User logged_user, User friend_user, LocalDateTime date_received,  Optional<String> message) {
        this.logged_user = logged_user;
        this.friend_user = friend_user;
        this.date_received = date_received;
        this.message = message;
    }

    public User getLogged_user() {
        return logged_user;
    }

    public User getFriend_user() {
        return friend_user;
    }

    public LocalDateTime getDate_received() {
        return date_received;
    }

    public Optional<String> getMessage() {
        return message;
    }

    @Override
    public String toString() {
        return "MessageDTO{" +
                "logged_user=" + logged_user +
                ", friend_user=" + friend_user +
                ", date_received=" + date_received +
                ", message=" + message +
                '}';
    }
}
