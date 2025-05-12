package ro.mpp.implementation;
import ro.mpp.*;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.List;
import java.util.Optional;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class ServicesRpcProxy implements Service{
    private final String host;
    private final int port;
    private Observer employeeObserver;
    private ObjectInputStream input;
    private ObjectOutputStream output;
    private Socket connection;
    private final BlockingQueue<Response> qresponses;
    private volatile boolean finished;

    public ServicesRpcProxy(String host, int port) {
        this.host = host;
        this.port = port;
        qresponses = new LinkedBlockingQueue<>();
    }

    public void logout(User employee, Observer client)
            throws Exception {
        Request req = new Request.Builder()
                .type(RequestType.LOGOUT)
                .data(employee)
                .build();
        sendRequest(req);
        Response response = readResponse();
        closeConnection();
        if (response.type() == ResponseType.ERROR) {
            String err = response.data().toString();
            throw new Exception(err);
        }
    }

    private void closeConnection() {
        finished = true;
        try {
            input.close();
            output.close();
            connection.close();
            employeeObserver = null;
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void sendRequest(Request request)
            throws Exception {
        try {
            output.writeObject(request);
            output.flush();
        } catch (IOException e) {
            throw new Exception("Error sending object " + e);
        }
    }

    private Response readResponse()
            throws Exception {
        Response response = null;
        try {
            response = qresponses.take();
        } catch (InterruptedException e) {
            throw new Exception("Reading response error " + e);
        }
        return response;
    }

    private void initializeConnection()
            throws Exception {
        try {
            connection = new Socket(host, port);
            output = new ObjectOutputStream(connection
                    .getOutputStream());
            output.flush();
            input = new ObjectInputStream(connection
                    .getInputStream());
            finished = false;
            startReader();
        } catch (IOException e) {
            throw new Exception("Error connecting to server " + e);
        }
    }

    private void startReader() {
        Thread tw = new Thread(new ReaderThread());
        tw.start();
    }

    private void handleUpdate(Response response){
        if(response.type() == ResponseType.UPDATE){
            Assigned assigned = (Assigned) response.data();
            if(employeeObserver == null){
                System.out.println("Employee " +
                        "observer is null");
            }else{
                try{
                    employeeObserver
                            .assignmentUpdated(assigned);
                }catch (Exception e){
                    System.out.println("" +
                            "Error updating employee " +
                            "observer " + e);
                }
            }
        }
    }

    private boolean isUpdate(Response response){
        return response.type() == ResponseType.UPDATE;
    }

    private class ReaderThread implements Runnable {
        @Override
        public void run() {
            while (!finished) {
                try {
                    Object response = input.readObject();
                    if (response instanceof Response r) {
                        System.out.println("[ReaderThread] " +
                                "Received response of type: " +
                                r.type());

                        if (isUpdate(r)) {
                            System.out.println("[ReaderThread] "+
                                    "Detected update");
                            handleUpdate(r);
                        } else {
                            System.out.println("[ReaderThread]"+
                                    " Putting response in queue");
                            qresponses.put(r);
                        }
                    }
                } catch (IOException | ClassNotFoundException
                         | InterruptedException e) {
                    System.out.println("Error in reader thread:" +
                            " " + e);
                }
            }
        }
    }

    @Override
    public User login(String username,
                      String password,
                      Observer client) throws Exception {
        initializeConnection();
        User user = new User(username,password,null);
        Request req = new Request.Builder()
                .type(RequestType.LOGIN)
                .data(user)
                .build();
        sendRequest(req);
        Response response = readResponse();
        if (response.type() == ResponseType.OK) {
            this.employeeObserver = client;
            return (User) response.data();
        } else{
            closeConnection();
            throw new Exception(response.data().toString());
        }
    }

    @Override
    public List<User> getAllUsers() throws Exception{
        Request req = new Request.Builder()
                .type(RequestType.GET_ALL_USERS)
                .build();
        sendRequest(req);
        Response response = readResponse();
        if(response.type() == ResponseType.ERROR){
            throw new Exception(response.data().toString());
        }
        return (List<User>) response.data();
    }

    @Override
    public List<Mission> getAllMissions()
            throws Exception{
        Request req = new Request.Builder()
                .type(RequestType.GET_ALL_MISSIONS)
                .build();
        sendRequest(req);
        Response response = readResponse();
        if(response.type() == ResponseType.ERROR){
            throw new Exception(response.data().toString());
        }
        return (List<Mission>) response.data();
    }


    @Override
    public Optional<Mission> findMissionById(Integer id)
            throws Exception{
        Request request = new Request.Builder()
                .type(RequestType.GET_MISSION_BY_ID)
                .build();
        sendRequest(request);
        Response response = readResponse();
        if (response.type() == ResponseType.ERROR) {
            throw new Exception(response.data().toString());
        }
        return Optional.ofNullable((Mission) response.data());
    }

    @Override
    public List<Mission> getFinishedMissions()
            throws Exception{
        Request request = new Request.Builder()
                .type(RequestType.GET_FINISHED_MISSIONS)
                .build();
        sendRequest(request);
        Response response = readResponse();
        if(response.type() == ResponseType.ERROR){
            throw new Exception(response.data().toString());
        }
        return (List<Mission>) response.data();
    }

    @Override
    public Mission addMission(Mission mission)
            throws Exception{
        Request request = new Request.Builder()
                .type(RequestType.ADD_MISSION)
                .data(mission).build();
        sendRequest(request);
        Response response = readResponse();
        if (response.type() == ResponseType.ERROR) {
            throw new Exception(response.data().toString());
        }
        return (Mission) response.data();
    }

    @Override
    public void deleteMission(Integer id)
            throws Exception{
        Request request = new Request.Builder()
                .type(RequestType.DELETE_MISSION)
                .data(id).build();
        sendRequest(request);
        Response response = readResponse();
        if (response.type() == ResponseType.ERROR) {
            throw new Exception(response.data().toString());
        }
    };

    @Override
    public List<Mission> getMissionsAssignedToUser(Integer userId)
            throws Exception{
        Request request = new Request.Builder()
                .type(RequestType.GET_MISSIONS_FOR_USER)
                .data(userId)
                .build();
        sendRequest(request);
        Response response = readResponse();
        if (response.type() == ResponseType.ERROR) {
            throw new Exception(response.data().toString());
        }
        return (List<Mission>) response.data();
    };

    @Override
    public Assigned assignMissionToUser(Assigned assigned)
            throws Exception{
        Request request = new Request.Builder()
                .type(RequestType.ASSIGN_MISSION_TO_USER)
                .data(assigned).build();
        sendRequest(request);
        Response response = readResponse();
        if (response.type() == ResponseType.ERROR) {
            throw new Exception(response.data().toString());
        }
        return (Assigned) response.data();
    };

    @Override
    public void uploadFileForAssignment(Integer assignedId,
                                        String fileName)
            throws Exception{
        Object[] data = new Object[]{assignedId, fileName};
        Request request = new Request.Builder()
                .type(RequestType.UPLOAD_FILE_FOR_ASSIGNMENT)
                .data(data)
                .build();
        sendRequest(request);
        Response response = readResponse();
        if (response.type() == ResponseType.ERROR) {
            throw new Exception(response.data().toString());
        }
    }

    @Override
    public void validateAssignment(Integer assignedId)
            throws Exception{
        Request request = new Request.Builder()
                .type(RequestType.VALIDATE_ASSIGNMENT)
                .data(assignedId).build();
        sendRequest(request);
        Response response = readResponse();
        if (response.type() == ResponseType.ERROR) {
            throw new Exception(response.data().toString());
        }
    };

    @Override
    public List<Assigned> getUnvalidatedAssignments()
            throws Exception{
        Request request = new Request.Builder()
                .type(RequestType.GET_UNVALIDATED_ASSIGNMENTS)
                .build();
        sendRequest(request);
        Response response = readResponse();
        if(response.type() == ResponseType.ERROR){
            throw new Exception(response.data().toString());
        }
        return (List<Assigned>) response.data();
    };

    @Override
    public List<Assigned> getAllAssignments()
            throws Exception{
        Request request = new Request.Builder()
                .type(RequestType.GET_ALL_ASSIGNMENTS).build();
        sendRequest(request);
        Response response = readResponse();
        if(response.type() == ResponseType.ERROR){
            throw new Exception(response.data().toString());
        }
        return (List<Assigned>) response.data();
    }

    @Override
    public void deleteAssignment(Integer id)
            throws Exception{
        Request request = new Request.Builder()
                .type(RequestType.DELETE_ASSIGNMENT)
                .data(id).build();
        sendRequest(request);
        Response response = readResponse();
        if (response.type() == ResponseType.ERROR) {
            throw new Exception(response.data().toString());
        }
    }

    @Override
    public List<Assigned> getAssignmentsForUser
            (Integer userId)throws Exception{
        Request request= new Request.Builder()
                .type(RequestType.ASSIGNEMENTS_FOR_USER)
                .data(userId).build();
        sendRequest(request);
        Response response = readResponse();
        if(response.type() == ResponseType.ERROR){
            throw new Exception(response.data().toString());
        }
        return (List<Assigned>) response.data();
    }
}
