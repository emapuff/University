package ro.mpp;

import jakarta.persistence.*;

import java.io.Serializable;
import java.time.LocalDate;
import java.util.Objects;

@Entity
@Table(name = "missions")
public class Mission extends BaseEntity implements Serializable {
    private static final long serialVersionUID = 1L;

    @Column(nullable = false)
    private LocalDate deadline;

    @Column(nullable = false, length = 500)
    private String description;

    @Column(nullable = false)
    private boolean finished;

    public Mission() {} // Constructor gol necesar

    public Mission(LocalDate deadline, String description, boolean finished) {
        this.deadline = deadline;
        this.description = description;
        this.finished = finished;
    }

    @Override
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    public Integer getId() {
        return super.getId();
    }

    public void setID(Integer id){
        super.setId(id);
    }

    public LocalDate getDeadline() { return deadline; }
    public void setDeadline(LocalDate deadline) { this.deadline = deadline; }

    public String getDescription() { return description; }
    public void setDescription(String description) { this.description = description; }

    public boolean isFinished() { return finished; }
    public void setFinished(boolean finished) { this.finished = finished; }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Mission mission)) return false;
        return finished == mission.finished &&
                Objects.equals(deadline, mission.deadline) &&
                Objects.equals(description, mission.description);
    }

    @Override
    public int hashCode() {
        return Objects.hash(deadline, description, finished);
    }

    @Override
    public String toString() {
        return "Mission{" +
                "deadline=" + deadline +
                ", description='" + description + '\'' +
                ", finished=" + finished +
                '}';
    }
}
