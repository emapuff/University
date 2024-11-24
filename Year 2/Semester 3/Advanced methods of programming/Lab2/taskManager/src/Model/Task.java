package Model;

import java.util.Objects;

public abstract class Task {
   private String taskId;
   private String descriere;

   public Task(String taskId, String descriere) {
       this.taskId = taskId;
       this.descriere = descriere;
   }

   public String getTaskId() {
       return taskId;
   }


   public String getDescriere() {
       return descriere;
   }

    public abstract void execute();

    @Override
    public String toString() {
        return taskId + "\t" + descriere + "\n";
    }

    @Override
    public boolean equals(Object obj) {
        if(this ==obj) return true;
        if( obj == null || getClass()!= obj.getClass() ) return false;

        Task task = (Task) obj; //cast la obj to Model.Task
        return Objects.equals(taskId, ((Task) obj).taskId);
    }

    @Override
    public int hashCode() {
        return Objects.hash(taskId);
    }
}
