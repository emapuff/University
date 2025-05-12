package ro.mpp;

import ro.mpp.implelemtation.AssignedRepositoryHibernate;
import ro.mpp.implelemtation.MissionRepositryHibernate;
import ro.mpp.implelemtation.UserRepositoryHibernate;
import ro.mpp.implementation.ServiceImpl;
import ro.mpp.util.HibernateUtil;
import ro.mpp.utils.AbstractServer;
import ro.mpp.utils.RpcConcurrentServer;
import ro.mpp.util.HibernateUtil;
import ro.mpp.utils.ServerException;
import org.hibernate.SessionFactory;
import java.io.IOException;
import java.util.Properties;

public class StartRpcServer {
    private static int defaultPort=55555;

    public static void main(String[] args) {
        HibernateUtil.getSessionFactory();
        Properties serverProps=new Properties();
        try {
            serverProps.load(StartRpcServer.class.getResourceAsStream("/server.properties"));
            System.out.println("Server properties set. ");
            serverProps.list(System.out);
        } catch (IOException e) {
            System.err.println("Cannot find server.properties "+e);
            return;
        }
        UserRepository userRepository = new UserRepositoryHibernate();
        MissionRepository missionRepository = new MissionRepositryHibernate();
        AssignedRepository assignedRepository = new AssignedRepositoryHibernate();
        Service serviceImpl = new ServiceImpl(userRepository, missionRepository, assignedRepository);

        int chatServerPort=defaultPort;
        try {
            chatServerPort = Integer.parseInt(serverProps.getProperty("server.port"));
        }catch (NumberFormatException nef){
            System.err.println("Wrong  Port Number"+nef.getMessage());
            System.err.println("Using default port "+defaultPort);
        }
        System.out.println("Starting server on port: "+chatServerPort);
        AbstractServer server = new RpcConcurrentServer(chatServerPort, serviceImpl);
        try {
            server.start();
        } catch (ServerException e) {
            System.err.println("Error starting the server" + e.getMessage());
        }finally {
            try {
                server.stop();
            }catch(ServerException e){
                System.err.println("Error stopping server "+e.getMessage());
            }
        }
    }
}
