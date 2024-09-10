#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dbms.h"
#include "../include/index.h"
#include "../include/query_executor.h"
#include "../include/storage.h"

#define DATABASE_FILE "database.txt"

void init_dbms() {
    // Initialize database system
    printf("Initializing DBMS...\n");

    // Create or open the database file
    FILE *file = fopen(DATABASE_FILE, "a"); // Open file for appending
    if (file == NULL) {
        perror("Failed to open database file");
        exit(EXIT_FAILURE);
    }
    fclose(file);
}

void create_record(const char *record) {
    FILE *file = fopen(DATABASE_FILE, "a"); // Open file for appending
    if (file == NULL) {
        perror("Failed to open database file");
        return;
    }
    fprintf(file, "%s\n", record); // Write the record to the file
    fclose(file);
    printf("Record added successfully.\n");
}

void read_record(const char *query) {
    FILE *file = fopen(DATABASE_FILE, "r"); // Open file for reading
    if (file == NULL) {
        perror("Failed to open database file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, query)) {
            printf("Found record: %s", line);
        }
    }
    fclose(file);
}

void update_record(const char *query) {
    // Implement update logic: read, modify, and write back
    // This is a placeholder implementation and should be adapted to your needs

    // Read records
    FILE *file = fopen(DATABASE_FILE, "r");
    if (file == NULL) {
        perror("Failed to open database file");
        return;
    }

    // Temporarily store records
    char temp_file[] = "temp.txt";
    FILE *temp = fopen(temp_file, "w");
    if (temp == NULL) {
        perror("Failed to open temporary file");
        fclose(file);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Modify record based on query
        // For simplicity, just write the line as is
        fprintf(temp, "%s", line);
    }

    fclose(file);
    fclose(temp);

    // Replace old file with new file
    remove(DATABASE_FILE);
    rename(temp_file, DATABASE_FILE);

    printf("Record updated successfully.\n");
}

void delete_record(const char *query) {
    // Implement delete logic: read, filter out the record, and write back

    // Read records
    FILE *file = fopen(DATABASE_FILE, "r");
    if (file == NULL) {
        perror("Failed to open database file");
        return;
    }

    // Temporarily store records
    char temp_file[] = "temp.txt";
    FILE *temp = fopen(temp_file, "w");
    if (temp == NULL) {
        perror("Failed to open temporary file");
        fclose(file);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (!strstr(line, query)) {
            fprintf(temp, "%s", line); // Write records that do not match the query
        }
    }

    fclose(file);
    fclose(temp);

    // Replace old file with new file
    remove(DATABASE_FILE);
    rename(temp_file, DATABASE_FILE);

    printf("Record deleted successfully.\n");
}

int main() {
    int choice;
    char buffer[256];

    // Initialize the DBMS
    init_dbms();

    while (1) {
        // Display menu
        printf("\nDBMS Menu:\n");
        printf("1. Create Record\n");
        printf("2. Read Record\n");
        printf("3. Update Record\n");
        printf("4. Delete Record\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        fgets(buffer, sizeof(buffer), stdin);
        choice = atoi(buffer);

        switch (choice) {
            case 1:
                printf("Enter record details: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
                create_record(buffer);
                break;
            case 2:
                printf("Enter query: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
                read_record(buffer);
                break;
            case 3:
                printf("Enter update query: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
                update_record(buffer);
                break;
            case 4:
                printf("Enter delete query: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
                delete_record(buffer);
                break;
            case 5:
                // Exit the program
                printf("Exiting...\n");
                // Cleanup code if necessary
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}
