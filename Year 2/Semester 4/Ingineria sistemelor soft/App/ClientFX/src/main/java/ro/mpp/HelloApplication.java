package ro.mpp;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import ro.mpp.controllers.LogInController;
import ro.mpp.implementation.ServicesRpcProxy;

import java.io.IOException;
import java.util.Properties;

public class HelloApplication extends Application {
    private static int defaultChatPort = 55555;
    private static String defaultServer = "localhost";

    @Override
    public void start(Stage primaryStage) {
        try {
            Properties props=new Properties();
            try {
                props.load(getClass().getResourceAsStream("/user.proprieties"));
                System.out.println("Found the file");
            } catch (IOException e) {
                System.out.println("Cannot find bd.config "+e);
            }
            String serverIp = props.getProperty("server.host", defaultServer);
            int serverPort = defaultChatPort;
            try {
                serverPort = Integer.parseInt(props.getProperty("server.port"));
            } catch (NumberFormatException ex) {
                System.err.println("Wrong port number " + ex.getMessage());
                System.out.println("Using default port: " + defaultChatPort);
            }
            System.out.println("Using server IP " + serverIp);
            System.out.println("Using server port " + serverPort);

            Service service = new ServicesRpcProxy(serverIp, serverPort);
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/login.fxml"));
            AnchorPane root = loader.load();
            LogInController loginController = loader.getController();
            loginController.initService(service);
            loginController.setPrimaryStage(primaryStage);
            Stage stage = new Stage();
            stage.setScene(new Scene(root));
            stage.setTitle("Login");
            stage.show();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        launch(args);
    }


}
