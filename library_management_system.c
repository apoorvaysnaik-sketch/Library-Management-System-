#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 50
#define FINE_PER_DAY 2.0

int id[MAX_BOOKS], issued[MAX_BOOKS];
char title[MAX_BOOKS][50], author[MAX_BOOKS][50];
int count = 0;

int findBook(int bookId);
void addBook(void);
void displayBooks(void);
void searchBook(void);
void issueBook(void);
void returnBook(void);
void deleteBook(void);
void calculateFine(void);

int main(void)
{
    char username[20], password[20];
    int choice;

    printf("===== LIBRARY MANAGEMENT SYSTEM =====\n");
    printf("\n===== LIBRARY LOGIN =====\n");

    printf("Username: ");
    scanf("%19s", username);

    printf("Password: ");
    scanf("%19s", password);

    if (strcmp(username, "admin") != 0 ||
        strcmp(password, "1234") != 0)
    {
        printf("Wrong username or password!\n");
        return 0;
    }

    printf("Login successful!\n");

    do
    {
        printf("\n===== LIBRARY MENU =====\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Book\n");
        printf("4. Issue Book\n");
        printf("5. Return Book\n");
        printf("6. Delete Book\n");
        printf("7. Calculate Fine\n");
        printf("8. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) { }
            choice = 0;
            continue;
        }

        switch (choice)
        {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                issueBook();
                break;
            case 5:
                returnBook();
                break;
            case 6:
                deleteBook();
                break;
            case 7:
                calculateFine();
                break;
            case 8:
                printf("Thank you!\n");
                break;
            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 8);

    return 0;
}

int findBook(int bookId)
{
    int i;
    for (i = 0; i < count; i++)
    {
        if (id[i] == bookId)
            return i;
    }
    return -1;
}

void addBook(void)
{
    int bookId;

    if (count >= MAX_BOOKS)
    {
        printf("Library is full!\n");
        return;
    }

    printf("Enter book ID: ");
    if (scanf("%d", &bookId) != 1)
    {
        printf("Invalid book ID!\n");
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) { }
        return;
    }

    if (findBook(bookId) != -1)
    {
        printf("Book ID already exists!\n");
        return;
    }

    id[count] = bookId;

    printf("Enter title (one word): ");
    scanf("%49s", title[count]);

    printf("Enter author (one word): ");
    scanf("%49s", author[count]);

    issued[count] = 0;
    count++;

    printf("Book added successfully!\n");
}

void displayBooks(void)
{
    int i;

    if (count == 0)
    {
        printf("No books available!\n");
        return;
    }

    printf("\n===== BOOK DETAILS =====\n");
    for (i = 0; i < count; i++)
    {
        printf("\nBook ID: %d\n", id[i]);
        printf("Title: %s\n", title[i]);
        printf("Author: %s\n", author[i]);

        if (issued[i] == 1)
            printf("Status: Issued\n");
        else
            printf("Status: Available\n");
    }
}

void searchBook(void)
{
    int bookId, index;

    printf("Enter book ID to search: ");
    if (scanf("%d", &bookId) != 1)
    {
        printf("Invalid book ID!\n");
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) { }
        return;
    }

    index = findBook(bookId);

    if (index == -1)
    {
        printf("Book not found!\n");
    }
    else
    {
        printf("Book found!\n");
        printf("Title: %s\n", title[index]);
        printf("Author: %s\n", author[index]);
        printf("Status: %s\n",
               issued[index] == 1 ? "Issued" : "Available");
    }
}

void issueBook(void)
{
    int bookId, index;

    printf("Enter book ID to issue: ");
    if (scanf("%d", &bookId) != 1)
    {
        printf("Invalid book ID!\n");
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) { }
        return;
    }

    index = findBook(bookId);

    if (index == -1)
        printf("Book not found!\n");
    else if (issued[index] == 1)
        printf("Book already issued!\n");
    else
    {
        issued[index] = 1;
        printf("Book issued successfully!\n");
    }
}

void returnBook(void)
{
    int bookId, index;

    printf("Enter book ID to return: ");
    if (scanf("%d", &bookId) != 1)
    {
        printf("Invalid book ID!\n");
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) { }
        return;
    }

    index = findBook(bookId);

    if (index == -1)
        printf("Book not found!\n");
    else if (issued[index] == 0)
        printf("Book was not issued!\n");
    else
    {
        issued[index] = 0;
        printf("Book returned successfully!\n");
    }
}

void deleteBook(void)
{
    int bookId, index, i;

    printf("Enter book ID to delete: ");
    if (scanf("%d", &bookId) != 1)
    {
        printf("Invalid book ID!\n");
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) { }
        return;
    }

    index = findBook(bookId);

    if (index == -1)
    {
        printf("Book not found!\n");
        return;
    }

    for (i = index; i < count - 1; i++)
    {
        id[i] = id[i + 1];
        strcpy(title[i], title[i + 1]);
        strcpy(author[i], author[i + 1]);
        issued[i] = issued[i + 1];
    }

    count--;
    printf("Book deleted successfully!\n");
}

void calculateFine(void)
{
    int days;
    float fine;

    printf("Enter number of overdue days: ");
    if (scanf("%d", &days) != 1 || days < 0)
    {
        printf("Invalid number of days!\n");
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) { }
        return;
    }

    fine = days * FINE_PER_DAY;

    printf("Fine rate: Rs. %.2f per day\n", FINE_PER_DAY);
    printf("Total library fine: Rs. %.2f\n", fine);
}
