#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>


//Oleh : Benjamin Khawarizmi Habibi
//NRP : 5027231078

#define MAX_PATH_LENGTH 256
#define DIRECTORY_TO_PROCESS "new-entry"

// Check if the file has an acceptable format
int isValidFile(const char *name) {
    size_t length = strlen(name);

    // Early out for names too short to be valid
    if (length < 5) {
        return 0;
    }

    // Check file extension and required substring
    const char *fileExt = name + length - 4;
    int hasValidExt = (strcmp(fileExt, ".csv") == 0);
    int hasKeyword = (strstr(name, "_trashcan") != NULL || strstr(name, "_parkinglot") != NULL);

    return hasValidExt && hasKeyword;
}

// Process files within specified directory
void processDirectory(const char *directoryName) {
    DIR *directory = opendir(directoryName);
    struct dirent *fileInfo;
    char pathBuffer[MAX_PATH_LENGTH];

    if (!directory) {
        perror("Failed to open directory");
        return;
    }

    // Read each file in the directory
    while ((fileInfo = readdir(directory)) != NULL) {
        if (fileInfo->d_type == DT_REG) {  // Ensure it's a regular file
            if (isValidFile(fileInfo->d_name)) {
                printf("Valid file: %s\n", fileInfo->d_name);
            } else {
                printf("Invalid file: %s\n", fileInfo->d_name);
                snprintf(pathBuffer, sizeof(pathBuffer), "%s/%s", directoryName, fileInfo->d_name);
                char *command[] = {"rm", pathBuffer, NULL};
                if (execvp(command[0], command) == -1) {
                    perror("Failed to delete file");
                }
            }
        }
    }

    closedir(directory);
}

int main() {
    processDirectory(DIRECTORY_TO_PROCESS);
    return 0;
}
