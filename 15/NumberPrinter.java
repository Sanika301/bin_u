public class NumberPrinter {
    public static void main(String[] args) {
        // Create and start threads
        Thread evenThread = new Thread(new EvenPrinter());
        Thread oddThread = new Thread(new OddPrinter());
        Thread primeThread = new Thread(new PrimePrinter());

        evenThread.start();
        oddThread.start();
        primeThread.start();
    }

    static class EvenPrinter implements Runnable {
        public void run() {
            for (int i = 2; i <= 10; i += 2) {
                System.out.println("Even: " + i);
                try {
                    Thread.sleep(500); // Sleep for 500 milliseconds
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    static class OddPrinter implements Runnable {
        public void run() {
            for (int i = 1; i <= 10; i += 2) {
                System.out.println("Odd: " + i);
                try {
                    Thread.sleep(500); // Sleep for 500 milliseconds
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    static class PrimePrinter implements Runnable {
        public void run() {
            for (int i = 2; i <= 10; i++) {
                if (isPrime(i)) {
                    System.out.println("Prime: " + i);
                    try {
                        Thread.sleep(500); // Sleep for 500 milliseconds
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }

        private boolean isPrime(int n) {
            if (n <= 1) {
                return false;
            }
            for (int i = 2; i <= Math.sqrt(n); i++) {
                if (n % i == 0) {
                    return false;
                }
            }
            return true;
        }
    }
}
