package ro.mpp;

import java.util.List;

public interface AssignedRepository extends CrudRepository<Integer, Assigned> {
    List<Mission> findMissionsByUserId(Integer userId);

    void uploadFile(Integer assignedId, String fileName);

    void validateAssignment(Integer assignedId);

    public List<Assigned> findUnvalidatedAssignments();
}
