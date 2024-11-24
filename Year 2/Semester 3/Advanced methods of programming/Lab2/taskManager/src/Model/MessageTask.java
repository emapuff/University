package Model;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class MessageTask extends Task{
    private String message;
    private String from;
    private String to;
    private LocalDateTime date;

    private static DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");

    public MessageTask(String message, String from, String to, LocalDateTime date, String taskId, String descriere){
        super(taskId, descriere);
        this.message = message;
        this.from = from;
        this.to = to;
        this.date = date;
    }

    @Override
    public void execute() {
        System.out.println("mesaj= "+message+"| date= "+date.format(formatter));
    }

    public String toString(){
        return "id="+this.getTaskId() +"|description=" + this.getDescriere() + "|message=" + message + "|from="
                + from + "|to =" + to + "|date =" + date.format(formatter);
    }



}
