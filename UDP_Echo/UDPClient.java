import java.io.*;
import java.net.*;
import java.util.Scanner;

public class UDPClient {

    public static void main(String args[]) throws IOException 

    { 
        Scanner sc = new Scanner(System.in); 
  
        DatagramSocket ds = new DatagramSocket(); 
  
        InetAddress ip = InetAddress.getLocalHost(); 
        byte buf[] = null; 
  
        while (true) 
        { 
            System.out.println("Enter Data to send:\n");
            String inp = sc.nextLine(); 
  
            buf = inp.getBytes(); 
  
          
            DatagramPacket DpSend = 
                  new DatagramPacket(buf, buf.length, ip, 8080); 
  
           
            ds.send(DpSend); 
  
            if (inp.equals("bye")) 
                break; 
        } 
    } 

    // public static void main(String[] args) throws IOException{

    //     Scanner sc = new Scanner(System.in);
    //     DatagramSocket socket = new DatagramSocket();
    //     InetAddress ip = InetAddress.getLocalHost();
        
    //     while(true){
    //         System.out.println("Enter Data to send:");
    //         String message = sc.nextLine();

    //         byte buf[] = message.getBytes();

    //         DatagramPacket packet = new DatagramPacket(buf,buf.length,ip,8080);
        
    //         socket.send(packet);
    //         if(message.equalsIgnoreCase("bye")){
    //             break;
    //         }



    //     }
        
    // }
}