package ro.mpp.utils;

import java.net.Socket;
import ro.mpp.Service;
import ro.mpp.implementation.ClientRpcReflectionWorker;

public class RpcConcurrentServer extends AbsConcurrentServer {
    private final Service chatServer;
    public RpcConcurrentServer(int port,
                               Service chatServer) {
        super(port);
        this.chatServer = chatServer;
    }

    @Override
    protected Thread createWorker(Socket client) {
        ClientRpcReflectionWorker worker=new
                ClientRpcReflectionWorker(chatServer, client);
        Thread tw=new Thread(worker);
        return tw;
    }

    @Override
    public void stop(){

    }
}
