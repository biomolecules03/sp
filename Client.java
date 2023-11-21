import java.rmi.*;
import java.util.*;

public class Client {
    public static void main(String[] args) throws Exception {
        AssignmentInterface object = (AssignmentInterface)Naming.lookup("METHODS");
        int choice;
        while (1 == 1) {
            System.out.print("===================================\n    1. For Counting characters\n    2. For adding numbers\nEnter your choice : ");
            Scanner sc = new Scanner(System.in);
            choice = sc.nextInt();
            switch (choice) {
                case 1 : {
                    System.out.print("Type something... ");
                    String input = sc.next();
                    System.out.println("You have typed " + object.countInput(input) + "  letters!!");
                    break;
                }case 2 : {
                    System.out.print("Enter 2 numbers : ");
                    int a = sc.nextInt(), b = sc.nextInt();
                    System.out.println("Sum = " + object.addNumbers(a,b));
                    break;
                } default : break;

            }
        }
    }
}
