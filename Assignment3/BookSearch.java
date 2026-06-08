
import java.util.ArrayList;
import java.util.Scanner;

public class BookSearch {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        ArrayList<String> books = new ArrayList<>();

        System.out.println("Enter book titles (type 'done' to stop):");

        while (true) {
            String title = sc.nextLine();
            if (title.equalsIgnoreCase("done")) {
                break;
            }
            books.add(title);
        }

        // display books
        System.out.println("\nAll Books:");
        for (String b : books) {
            System.out.println(b);
        }

        // search
        System.out.print("\nEnter word to search: ");
        String word = sc.nextLine().toLowerCase();

        System.out.println("Matching Books:");
        boolean found = false;

        for (String title : books) {
            if (title.toLowerCase().contains(word)) {
                System.out.println(title);
                found = true;
            }
        }

        if (!found) {
            System.out.println("No book found.");
        }

        sc.close();
    }
}