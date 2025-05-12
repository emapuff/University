package ro.mpp.implementation;

import ro.mpp.*;

import javax.security.auth.login.LoginException;
import java.io.File;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.concurrent.ConcurrentHashMap;

public class ServiceImpl implements Service {
    private final UserRepository userRepository;
    private final MissionRepository missionRepository;
    private final AssignedRepository assignedRepository;
    private final Map<String, Observer> loggedUsers;

    public ServiceImpl(UserRepository userRepository,
                       MissionRepository missionRepository,
                       AssignedRepository assignedRepository) {
        this.userRepository = userRepository;
        this.missionRepository = missionRepository;
        this.assignedRepository = assignedRepository;
        loggedUsers = new ConcurrentHashMap<>();
    }

    @Override
    public synchronized User login(String email,
                                   String password,
                                   Observer observer)
        throws Exception {

        User user = userRepository
                .findByEmailAndPassword(email,password);
        if(user == null) {
            throw new LoginException("Invalid username or password");
        }
        if(loggedUsers.containsKey(user.getEmail())) {
            throw new LoginException("User already logged in");
        }
        loggedUsers.put(user.getEmail(), observer);
        return user;
    }

    @Override
    public synchronized  void logout(User employee, Observer client) throws Exception{
        Observer localClient = loggedUsers.remove(employee.getEmail());
        if(localClient == null) {
            throw new Exception("The user is not logged in" + employee.getName());
        }
    }

    @Override
    public synchronized List<User> getAllUsers() throws Exception{
        return userRepository.findAll();
    }

    @Override
    public synchronized List<Mission> getAllMissions() throws Exception{
        return missionRepository.findAll();
    }

    @Override
    public synchronized void deleteMission(Integer id) throws Exception {
        Optional<Mission> mission = missionRepository.findById(id);
        if (mission.isEmpty() || mission.get().getId() == null) {
            throw new IllegalArgumentException("Mission or mission ID cannot be null");
        }

        List<Assigned> assignedList = assignedRepository.findAll().stream()
                .filter(a -> a.getMission().getId().equals(mission.get().getId()))
                .toList();

        if (!assignedList.isEmpty()) {
            throw new Exception("Mission cannot be deleted: it has active assignments.");
        }

        missionRepository.delete(mission.get().getId());
    }

    @Override
    public synchronized Optional<Mission> findMissionById(Integer id) throws Exception{
        return missionRepository.findById(id);
    }

    @Override
    public synchronized List<Mission> getFinishedMissions() throws Exception {
        return missionRepository.findAll().stream()
                .filter(Mission::isFinished)
                .toList();
    }

    @Override
    public synchronized Mission addMission(Mission mission) throws Exception{
        return missionRepository.save(mission);
    }

    @Override
    public synchronized List<Mission> getMissionsAssignedToUser(Integer id) throws Exception {
        return assignedRepository.findMissionsByUserId(id);
    }

    @Override
    public synchronized Assigned assignMissionToUser(Assigned assignment) throws Exception {
        if (assignment == null ||
                assignment.getUser() == null ||
                assignment.getMission() == null ||
                assignment.getUser().getId() == null ||
                assignment.getMission().getId() == null) {
            throw new IllegalArgumentException("Assigned object must contain valid user and mission");
        }
        return assignedRepository.save(assignment);
    }

    @Override
    public synchronized void uploadFileForAssignment(Integer assignedId, String fileName) throws Exception {
        assignedRepository.uploadFile(assignedId, fileName);
        Optional<Assigned> opt = assignedRepository.findById(assignedId);
        if (opt.isEmpty()) {
            throw new IllegalArgumentException("Assignment not found: " + assignedId);
        }

        Assigned updated = opt.get();
        String uploaderEmail = updated.getUser().getEmail();

        // Notify all observers except the uploader
        for (Map.Entry<String, Observer> entry : loggedUsers.entrySet()) {
            String email = entry.getKey();
            Observer obs = entry.getValue();
            if (!email.equals(uploaderEmail)) {
                try {
                    obs.assignmentUpdated(updated);
                } catch (Exception e) {
                    System.err.println("Failed notifying observer " + email + ": " + e.getMessage());
                }
            }
        }
    }


    @Override
    public synchronized void validateAssignment(Integer assignedId)throws Exception{
        assignedRepository.validateAssignment(assignedId);
    }

    @Override
    public synchronized List<Assigned> getUnvalidatedAssignments()throws Exception{
        return assignedRepository.findUnvalidatedAssignments();
    }

    @Override
    public synchronized List<Assigned> getAllAssignments()throws Exception{
        return assignedRepository.findAll();
    }

    @Override
    public synchronized void deleteAssignment(Integer id)throws Exception{
        assignedRepository.delete(id);
    }

    @Override
    public synchronized List<Assigned> getAssignmentsForUser
            (Integer id) throws Exception{
        return assignedRepository.getAssignmentsForUser(id);
    }

}
