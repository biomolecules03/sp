import java.rmi.*;
import java.rmi.server.*;

public class AssignmentMethods extends UnicastRemoteObject implements AssignmentInterface{
    public AssignmentMethods() throws RemoteException{
        System.out.println("Remote Server is running Now.!!");
    }
    @Override
    public int countInput(String input) throws RemoteException{ return input.length() ;}
    @Override
    public int addNumbers(int a, int b) throws RemoteException{ return a + b ; }
}
