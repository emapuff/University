package ro.mpp.implementation;

import ro.mpp.*;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.Socket;
import java.util.List;

public class ClientRpcReflectionWorker implements Runnable,
        Observer {
    private final Service service;
    private final Socket connection;
    private ObjectInputStream input;
    private ObjectOutputStream output;
    private volatile boolean connected;

    public ClientRpcReflectionWorker(Service service,
                                     Socket connection) {
        this.service = service;
        this.connection = connection;
        try{
            output=new ObjectOutputStream(connection
                    .getOutputStream());
            output.flush();
            input=new ObjectInputStream(connection
                    .getInputStream());
            connected=true;
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void run() {
        while(connected){
            try {
                Object request=input.readObject();
                Response response=
                        handleRequest((Request)request);
                if (response!=null){
                    sendResponse(response);
                }
            } catch (IOException | ClassNotFoundException e) {
                e.printStackTrace();
                System.out.println("Client rpc exception");
            }
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
                System.out.println("Interrupted");
            }
        }
        try {
            input.close();
            output.close();
            connection.close();
        } catch (IOException e) {
            System.out.println("Error " +
                    "in worker (closing connection): "+e);
        }
    }

    private static final Response okResponse=
            new Response.Builder()
                    .type(ResponseType.OK)
                    .build();

    private Response handleRequest(Request request){
        Response response=null;
        String handlerName="handle"+(request).type();
        try {
            Method method=this.getClass()
                    .getDeclaredMethod(handlerName,
                            Request.class);
            response=(Response)method
                    .invoke(this,request);
        } catch (NoSuchMethodException |
                 InvocationTargetException |
                 IllegalAccessException e) {
            e.printStackTrace();
            System.out.println("Error in worker" +
                    " (invoking method handleRequest): "+e);
        }
        return response;
    }

    private Response handleLOGIN(Request request){
        User user = (User) request.data();
        try {
            String email = user.getEmail();
            String password = user.getPassword();
            User foundEmployee = service
                    .login(email, password, this);
            return new Response.Builder()
                    .type(ResponseType.OK)
                    .data(foundEmployee)
                    .build();
        } catch (Exception e) {
            connected=false;
            return new Response.Builder()
                    .type(ResponseType.ERROR)
                    .data(e.getMessage())
                    .build();
        }
    }

    private Response handleLOGOUT(Request request){
        User user = (User) request.data();
        try{
            service.logout(user,this);
            connected = false;
            return okResponse;
        }catch(Exception e){
            return new Response.Builder()
                    .type(ResponseType.ERROR)
                    .data(e.getMessage())
                    .build();
        }
    }


    private Response handleGET_ALL_USERS(Request request) {
        try {
            List<User> users = service.getAllUsers();
            return new Response.Builder()
                    .type(ResponseType.GET_ALL_USERS)
                    .data(users)
                    .build();
        } catch (Exception e) {
            return new Response.Builder()
                    .type(ResponseType.ERROR)
                    .data(e.getMessage())
                    .build();
        }
    }

    private Response handleGET_ALL_MISSIONS(Request request) {
        try {
            List<Mission> missions = service.getAllMissions();
            return new Response.Builder()
                    .type(ResponseType.GET_ALL_MISSIONS)
                    .data(missions)
                    .build();
        } catch (Exception e) {
            return new Response.Builder()
                    .type(ResponseType.ERROR)
                    .data(e.getMessage())
                    .build();
        }
    }

    private Response handleADD_MISSION(Request request) {
        try {
            Mission mission = (Mission) request.data();
            Mission saved = service.addMission(mission);
            return new Response.Builder()
                    .type(ResponseType.OK)
                    .data(saved)
                    .build();
        } catch (Exception e) {
            return new Response.Builder()
                    .type(ResponseType.ERROR)
                    .data(e.getMessage())
                    .build();
        }
    }

    private Response handleDELETE_MISSION(Request request) {
        try {
            Integer id = (Integer) request.data();
            service.deleteMission(id);
            return new Response.Builder()
                    .type(ResponseType.OK)
                    .build();
        } catch (Exception e) {
            return new Response.Builder()
                    .type(ResponseType.ERROR)
                    .data(e.getMessage())
                    .build();
        }
    }

    private Response handleGET_MISSION_BY_ID(Request request) {
        try {
            Integer id = (Integer) request.data();
            Mission mission = service
                    .findMissionById(id)
                    .orElse(null);
            return new Response.Builder()
                    .type(ResponseType.GET_MISSION_BY_ID)
                    .data(mission).build();
        } catch (Exception e) {
            return new Response.Builder()
                    .type(ResponseType.ERROR)
                    .data(e.getMessage())
                    .build();
        }
    }

    private Response handleGET_FINISHED_MISSIONS(Request request) {
        try {
            List<Mission> missions = service
                    .getFinishedMissions();
            return new Response.Builder()
                    .type(ResponseType.GET_FINISHED_MISSIONS)
                    .data(missions).build();
        } catch (Exception e) {
            return new Response.Builder()
                    .type(ResponseType.ERROR)
                    .data(e.getMessage())
                    .build();
        }
    }

    private Response handleGET_MISSIONS_FOR_USER(Request request) {
        try {
            Integer userId = (Integer) request.data();
            List<Mission> missions = service
                    .getMissionsAssignedToUser(userId);
            return new Response.Builder()
                    .type(ResponseType.GET_MISSIONS_FOR_USER)
                    .data(missions)
                    .build();
        } catch (Exception e) {
            return new Response.Builder()
                    .type(ResponseType.ERROR)
                    .data(e.getMessage())
                    .build();
        }
    }

    private Response handleASSIGN_MISSION_TO_USER(Request request) {
        try {
            Assigned assignment = (Assigned) request.data();
            Assigned saved = service
                    .assignMissionToUser(assignment);
            return new Response.Builder()
                    .type(ResponseType.OK)
                    .data(saved)
                    .build();
        } catch (Exception e) {
            return new Response.Builder()
                    .type(ResponseType.ERROR)
                    .data(e.getMessage())
                    .build();
        }
    }

    private Response handleUPLOAD_FILE_FOR_ASSIGNMENT
            (Request request) {
        try {
            Object[] data = (Object[]) request.data();
            Integer assignedId = (Integer) data[0];
            String fileName = (String) data[1];
            service.uploadFileForAssignment(assignedId, fileName);
            return new Response.Builder()
                    .type(ResponseType.OK)
                    .build();
        } catch (Exception e) {
            return new Response.Builder()
                    .type(ResponseType.ERROR)
                    .data(e.getMessage())
                    .build();
        }
    }

    private Response handleVALIDATE_ASSIGNMENT(Request request) {
        try {
            Integer assignedId = (Integer) request.data();
            service.validateAssignment(assignedId);
            return new Response.Builder()
                    .type(ResponseType.OK)
                    .build();
        } catch (Exception e) {
            return new Response.Builder()
                    .type(ResponseType.ERROR)
                    .data(e.getMessage())
                    .build();
        }
    }

    private Response handleGET_UNVALIDATED_ASSIGNMENTS
            (Request request) {
        try {
            List<Assigned> assignments = service
                    .getUnvalidatedAssignments();
            return new Response.Builder()
                    .type(ResponseType.GET_UNVALIDATED_ASSIGNMENTS)
                    .data(assignments).build();
        } catch (Exception e) {
            return new Response.Builder()
                    .type(ResponseType.ERROR)
                    .data(e.getMessage())
                    .build();
        }
    }

    private Response handleGET_ALL_ASSIGNMENTS(Request request) {
        try {
            List<Assigned> assignments = service
                    .getAllAssignments();
            return new Response.Builder()
                    .type(ResponseType.GET_ALL_ASSIGNMENTS)
                    .data(assignments)
                    .build();
        } catch (Exception e) {
            return new Response.Builder()
                    .type(ResponseType.ERROR)
                    .data(e.getMessage())
                    .build();
        }
    }

    private Response handleDELETE_ASSIGNMENT(Request request) {
        try {
            Integer id = (Integer) request.data();
            service.deleteAssignment(id);
            return new Response.Builder()
                    .type(ResponseType.OK)
                    .build();
        } catch (Exception e) {
            return new Response.Builder()
                    .type(ResponseType.ERROR)
                    .data(e.getMessage())
                    .build();
        }
    }

    private Response handleASSIGNEMENTS_FOR_USER(Request request) {
        try {
            List<Assigned> assignments = service
                    .getAllAssignments();
            return new Response.Builder()
                    .type(ResponseType.ASSIGNEMENTS_FOR_USER)
                    .data(assignments)
                    .build();
        } catch (Exception e) {
            return new Response.Builder()
                    .type(ResponseType.ERROR)
                    .data(e.getMessage())
                    .build();
        }
    }

    @Override
    public void assignmentUpdated(Assigned assignment)
            throws Exception{
        Response response = new Response.Builder()
                .type(ResponseType.UPDATE)
                .data(assignment)
                .build();
        try{
            sendResponse(response);
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    private void sendResponse(Response response) {
        try {
            output.writeObject(response);
            output.flush();
        } catch (IOException e) {
            System.out.println("Error sending response");
        }
    }

}
