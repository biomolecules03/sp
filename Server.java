import java.rmi.*;
import java.rmi.server.*;

public class Server {
    public static void main(String arg[]){
        try{
            AssignmentMethods object = new AssignmentMethods();
            Naming.rebind("METHODS", object);
        } catch(Exception e){ System.out.println("Exception occurred : " + e.getMessage()); }
    }
}
