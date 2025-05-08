package ro.mpp;

import jakarta.persistence.*;

import java.io.Serializable;
import java.util.Objects;

@Entity
@Table(name = "assigned")
public class Assigned extends BaseEntity implements Serializable {
    private static final long serialVersionUID = 1L;

    @ManyToOne
    @JoinColumn(name = "user_id", referencedColumnName = "id", nullable = false)
    private User user;

    @ManyToOne
    @JoinColumn(name = "mission_id", referencedColumnName = "id", nullable = false)
    private Mission mission;

    @Column
    private String uploadFileName;

    @Column(nullable = false)
    private boolean validated = false;

    public Assigned() {}

    public Assigned(User user, Mission mission) {
        this.user = user;
        this.mission = mission;
    }

    @Override
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    public Integer getId() {
        return super.getId();
    }

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }

    public Mission getMission() {
        return mission;
    }

    public void setMission(Mission mission) {
        this.mission = mission;
    }

    public String getUploadFileName() {
        return uploadFileName;
    }

    public void setUploadFileName(String uploadFileName) {
        this.uploadFileName = uploadFileName;
    }

    public boolean isValidated() {
        return validated;
    }

    public void setValidated(boolean validated) {
        this.validated = validated;
    }

    @Override
    public String toString() {
        return "Assigned{" +
                "user=" + user +
                ", mission=" + mission +
                ", uploadFileName='" + uploadFileName + '\'' +
                ", validated=" + validated +
                '}';
    }
}
