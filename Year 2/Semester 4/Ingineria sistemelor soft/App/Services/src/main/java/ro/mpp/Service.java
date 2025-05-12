package ro.mpp;

import java.util.List;
import java.util.Optional;

public interface Service {
    User login(String username, String password, Observer observer) throws Exception;
    void logout(User user, Observer observer) throws Exception;
    List<User> getAllUsers() throws Exception;
    List<Mission> getAllMissions() throws Exception;
    Optional<Mission> findMissionById(Integer id) throws Exception;
    List<Mission> getFinishedMissions()throws Exception;
    Mission addMission(Mission mission)throws Exception;
    void deleteMission(Integer id)throws Exception;
    List<Mission> getMissionsAssignedToUser(Integer userId)throws Exception;
    Assigned assignMissionToUser(Assigned assigned)throws Exception;
    void uploadFileForAssignment(Integer assignedId, String fileName)throws Exception;
    void validateAssignment(Integer assignedId)throws Exception;
    List<Assigned> getUnvalidatedAssignments()throws Exception;
    List<Assigned> getAllAssignments()throws Exception;
    void deleteAssignment(Integer id)throws Exception;
    List<Assigned> getAssignmentsForUser(Integer userId)throws Exception;
}
