import java.io.*;
import java.net.*;
import java.util.*;

public class ChatServer {
    private static final int PORT = 12345;
    private static Set<String> usernames = new HashSet<>();
    private static List<ClientHandler> clients = new ArrayList<>();

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            System.out.println("Chat server is running on port " + PORT);
            
            while (true) {
                Socket clientSocket = serverSocket.accept();
                System.out.println("New client connected: " + clientSocket);
                
                ClientHandler clientHandler = new ClientHandler(clientSocket);
                clients.add(clientHandler);
                clientHandler.start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static class ClientHandler extends Thread {
        private Socket clientSocket;
        private PrintWriter out;
        private BufferedReader in;
        private String username;

        public ClientHandler(Socket socket) {
            this.clientSocket = socket;
        }

        public void run() {
            try {
                out = new PrintWriter(clientSocket.getOutputStream(), true);
                in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

                out.println("Welcome to the chat server! Please enter your username:");
                username = in.readLine();

                synchronized (usernames) {
                    while (usernames.contains(username)) {
                        out.println("Username already taken. Please choose another one:");
                        username = in.readLine();
                    }
                    usernames.add(username);
                }

                out.println("Welcome, " + username + "!");

                String input;
                while ((input = in.readLine()) != null) {
                    if (input.equalsIgnoreCase("/quit")) {
                        break;
                    }
                    broadcast(username + ": " + input);
                }
            } catch (IOException e) {
                e.printStackTrace();
            } finally {
                try {
                    if (username != null) {
                        synchronized (usernames) {
                            usernames.remove(username);
                        }
                        System.out.println(username + " has left the chat.");
                    }
                    if (clientSocket != null) {
                        clientSocket.close();
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

        private void broadcast(String message) {
            synchronized (clients) {
                for (ClientHandler client : clients) {
                    client.out.println(message);
                }
            }
        }
    }
}
