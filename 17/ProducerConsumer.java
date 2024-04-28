import java.util.LinkedList;

public class ProducerConsumer {
    private static final int BUFFER_SIZE = 5;
    private LinkedList<Integer> buffer = new LinkedList<>();
    
    public static void main(String[] args) {
        ProducerConsumer pc = new ProducerConsumer();
        Thread producerThread = new Thread(() -> pc.produce());
        Thread consumerThread = new Thread(() -> pc.consume());
        
        producerThread.start();
        consumerThread.start();
    }
    
    public void produce() {
        while (true) {
            synchronized (buffer) {
                while (buffer.size() == BUFFER_SIZE) {
                    try {
                        buffer.wait();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                
                int item = (int) (Math.random() * 100);
                buffer.add(item);
                System.out.println("Produced: " + item);
                
                buffer.notify(); // Notify consumer that an item is available
            }
            
            try {
                Thread.sleep((long) (Math.random() * 1000));
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
    
    public void consume() {
        while (true) {
            synchronized (buffer) {
                while (buffer.isEmpty()) {
                    try {
                        buffer.wait();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                
                int item = buffer.removeFirst();
                System.out.println("Consumed: " + item);
                
                buffer.notify(); // Notify producer that buffer has space
            }
            
            try {
                Thread.sleep((long) (Math.random() * 1000));
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
