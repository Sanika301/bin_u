import java.io.IOException;
import java.net.*;

public class UDPServer {
    public static void main(String[] args) throws IOException 
    { 
        DatagramSocket socket = new DatagramSocket(8080); 
        byte[] receive = new byte[1024]; 
  
        DatagramPacket packet = null; 

       
        while (true) 
        { 
  
            // Step 2 : create a DatgramPacket to receive the data. 
            packet = new DatagramPacket(receive, receive.length); 
  
            // Step 3 : revieve the data in byte buffer. 
            socket.receive(packet); 
  
            String message = new String(packet.getData(), 0, packet.getLength());
            System.out.println("Client: " + message); 
  
            // Exit the server if the client sends "bye" 
            if (message.equals("bye")) { 
                System.out.println("Client sent bye.....EXITING"); 
                break; 
            } 
  
            // Clear the buffer after every message. 
            receive = new byte[1024]; 
        } 
    } 

    
  
}