#include "../cpu/types.h"
#include "../libc/include/string.h"
#include "../drivers/screen.h"

// Size definations Hard coded for now
#define MAX_FILES 10
#define MAX_FILENAME_LENGTH 24
#define MAX_FILE_SIZE 1024

// file node
typedef struct 
{
    char name[MAX_FILENAME_LENGTH];
    char data[MAX_FILE_SIZE];
    u32 size;
}File;

typedef struct
{
    File files[MAX_FILES];
    u32 file_count;
}FileSystem;

FileSystem fs;


void init_file_system(){
    kprint("\nLoading file system modules\n");
    fs.file_count = 0;
}

// Create a new file
int create_file(const char *name) {
    if (fs.file_count >= MAX_FILES) {
        return -1; // File system full
    }
    for (int i = 0; i < fs.file_count; i++) {
        if (strncmp(fs.files[i].name, name, MAX_FILENAME_LENGTH) == 0) {
            return -2; // File already exists
        }
    }
    // Copy the filename
    for (int i = 0; i < MAX_FILENAME_LENGTH && name[i] != '\0'; i++) {
        fs.files[fs.file_count].name[i] = name[i];
    }
    fs.files[fs.file_count].size = 0;
    fs.file_count++;
    return 0; // Success
}

// Write data to a file
int write_file(const char *name, const char *data, u32 size) {
    for (int i = 0; i < fs.file_count; i++) {
        if (strncmp(fs.files[i].name, name, MAX_FILENAME_LENGTH) == 0) {
            if (size > MAX_FILE_SIZE) {
                return -1; // Data too large
            }
            for (u32 j = 0; j < size; j++) {
                fs.files[i].data[j] = data[j];
            }
            fs.files[i].size = size;
            return 0; // Success
        }
    }
    return -2; // File not found
}

// Read data from a file
int read_file(const char *name, char *buffer, u32 size) {
    for (int i = 0; i < fs.file_count; i++) {
        if (strncmp(fs.files[i].name, name, MAX_FILENAME_LENGTH) == 0) {
            if (size > fs.files[i].size) {
                size = fs.files[i].size; // Adjust size if too large
            }
            for (u32 j = 0; j < size; j++) {
                buffer[j] = fs.files[i].data[j];
            }
            return size; // Return number of bytes read
        }
    }
    return -1; // File not found
}

// Delete a file
int delete_file(const char *name) {
    for (int i = 0; i < fs.file_count; i++) {
        if (strncmp(fs.files[i].name, name, MAX_FILENAME_LENGTH) == 0) {
            // Shift files to fill the gap
            for (int j = i; j < fs.file_count - 1; j++) {
                fs.files[j] = fs.files[j + 1];
            }
            fs.file_count--;
            return 0; // Success
        }
    }
    return -1; // File not found
}

// Function to display all file names
void display_file_names() {
    kprint("\nCurrent Files in the File System:\n");
    for (int i = 0; i < fs.file_count; i++) {
        kprint(fs.files[i].name);
        kprint("\n");
    }
}