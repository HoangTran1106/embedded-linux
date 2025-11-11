#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[]) {
    struct stat file_stat;
    char time_str[100];
    
    // Check if file path argument is provided
    if (argc != 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }
    
    // Get file information using lstat()
    if (lstat(argv[1], &file_stat) == -1) {
        perror("lstat");
        return 1;
    }
    
    // Display File Path
    printf("=== FILE INFORMATION ===\n");
    printf("File Path: %s\n", argv[1]);
    
    // Determine and display File Type
    printf("File Type: ");
    if (S_ISREG(file_stat.st_mode)) {
        printf("Regular File\n");
    } else if (S_ISDIR(file_stat.st_mode)) {
        printf("Directory\n");
    } else if (S_ISLNK(file_stat.st_mode)) {
        printf("Symbolic Link\n");
    } else {
        printf("Other\n");
    }
    
    // Display Size
    printf("Size: %ld bytes\n", file_stat.st_size);
    
    // Display Last Modified time
    // Convert timestamp to human-readable format
    struct tm *timeinfo = localtime(&file_stat.st_mtime);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("Last Modified: %s\n", time_str);
    
    // Alternative: Using ctime() - simpler but less control over format
    // printf("Last Modified: %s", ctime(&file_stat.st_mtime));
    
    printf("========================\n");
    
    return 0;
}
