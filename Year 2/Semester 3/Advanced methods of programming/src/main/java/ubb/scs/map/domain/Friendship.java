package ubb.scs.map.domain;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Friendship extends Entity<Tuple<User,User>>{
    private final DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
    private LocalDateTime date;
    private final User u1;
    private final User u2;


    public Friendship(User u1, User u2) {
        this.u1 = (u1.getId().compareTo(u2.getId()) <= 0) ? u1 : u2;
        this.u2 = (u1.getId().compareTo(u2.getId()) > 0) ? u1 : u2;
    }


    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    public User getU1() {
        return u1;
    }

    public User getU2() {
        return u2;
    }

    @Override
    public String toString() {
        return "Friendship{" +
                "user1=" + u1.getFirstName() + // afișăm doar emailul sau un alt identificator
                ", user2=" + u2.getFirstName() +
                ", date=" + date.format(formatter) +
                '}';
    }
}
