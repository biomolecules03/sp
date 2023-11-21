import java.rmi.*;

interface AssignmentInterface extends Remote {
    public int countInput(String input)throws RemoteException;
    public int addNumbers(int a, int b)throws RemoteException;
}
