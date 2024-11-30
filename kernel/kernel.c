#include "../drivers/screen.h"
#include "util.h"
#include "../drivers/io.h"
#include "kbd.h"
#include "../libc/include/string.h"
#include "../kprograms/art.h"
#include "../kprograms/date.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../cpu/types.h"


#include "man.h"


// Filesystem--CODE---------------------- // 

// Size definations Hard coded for now
#define MAX_FILES 10
#define MAX_FILENAME_LENGTH 24
#define MAX_FILE_SIZE 1024

// file node
typedef struct 
{
    char name[MAX_FILENAME_LENGTH];
    char data[MAX_FILE_SIZE];
    int size;
}File;

typedef struct
{
    File files[MAX_FILES];
    int file_count;
}FileSystem;

FileSystem fs;


void init_file_system(){
    printF("\nLoading file system modules\n");
    fs.file_count = 0;
	// for (int i = 0; i < MAX_FILES; i++)
	// {
	// 	fs.files[i].name[0] = '\0';
	// }
	
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
int write_file(const char *name, const char *data, int size) {
    for (int i = 0; i < fs.file_count; i++) {
        if (strncmp(fs.files[i].name, name, MAX_FILENAME_LENGTH) == 0) {
            if (size > MAX_FILE_SIZE) {
                return -1; // Data too large
            }
            for (int j = 0; j < size; j++) {
                fs.files[i].data[j] = data[j];
            }
            fs.files[i].size = size;
            return 0; // Success
        }
    }
    return -2; // File not found
}

// Read data from a file
int read_file(const char *name, char *buffer, int size) {
    for (int i = 0; i < fs.file_count; i++) {
        if (strncmp(fs.files[i].name, name, MAX_FILENAME_LENGTH) == 0) {
            if (size > fs.files[i].size) {
                size = fs.files[i].size; // Adjust size if too large
            }
            for (int j = 0; j < size; j++) {
                buffer[j] = fs.files[i].data[j];
            }
            return size; // Return number of bytes read
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

// Filesystem END ------------------- //

void kernel_early(void) {
	clear_screen();
	//Program printing the art
	art();
	kprint("Loading interrupts\n");
	isr_install(); 
	//kprint("Loading process modules\n");
	
	//Loading file_system modules
	init_file_system();
	// Loading files
	create_file("setups.txt");
	write_file("setups.txt", "sample text hahahaha", 50);
	create_file("sample.txt");
	write_file("sample.txt", "Another text file", 23);

	//Testing the printf
	u32 test = 12;
	kprint("help command is available to help you to get started\n");
	//printf to avoid conflicts system libraries
	printF("Testing printf module\n%d, %d, %s \n", test,20, "Jex OS 2024");
	printF("\nWelcome to Jex OS a simple level zero monolific operating operating system\n");
	printF("\t\tCreated for the sole purpose of \n\t\t\t studying and understanding how OS's are created and operate\n");
	
    /* Test the interrupts */
    //__asm__ __volatile__("int $2");
    //__asm__ __volatile__("int $3");
}

int main(void){
	char *buff;
	strcpy(&buff[strlen(buff)], '1');
	kprint("\nWelcome to the kernel shell (press enter to continue): ");
	
	while(1){
		u8 byte;
		 while(byte = scan()){
		 	if(byte == 0x1c){ //0x1c is the enter button hex code
				if(strlen(buff)>0 && strcmp(buff, "help") == 0)
		 		{	
		 			kprint("\nThese are the avaible kernel shell commands:");
					kprint("\nhelp: prints all the commands");
					kprint("\nexit: prints Goodbye and shuts down the system");
					kprint("\nclear: clears the screen");
					kprint("\nintro: Os Development details");
					kprint("\nart: prints the boot up art");
					kprint("\nls: Display files");
					kprint("\nprinciples: Os Development details");
					kprint("\narchitecture: Display OS Architecture types");
					kprint("\ncomponents: Display Key Components of an Operating System");
					kprint("\ndevelopment process: Display Development Process of an Operating System");
					kprint("\nchallenges in os development: Display Challenges in OS Development");
					kprint("\nfuture trends: Display Future Trends in OS Development");
					

		 		}
		 		if(strlen(buff)>0 && strcmp(buff, "exit") == 0 )
		 		{
					kprint("\nGoodbye\n");
					shutdown_power_off ();
				}
		 		//TO ADD SIMPLY PUT IN IF AND CORESPODNING COMMAND
		 		if(strlen(buff)>0 && strcmp(buff, "clear") == 0)
		 		{	
					kprint("\nclear");
		 			clear_screen();
		 		}
				// Art command
				if(strlen(buff)>0 && strcmp(buff, "art") == 0)
		 		{
					kprint("\n");
		 			art();
		 		}
				// STILL UNDER CONSTRUCTION !!!
				//Time command
				// if(strlen(buff)>0 && strcmp(buff, "time") == 0)
		 		// {
		 		// 	rtc_get_time ();
		 		// }

				//Timer command //WARNING INFINITE LOOP JUST FOR TESTING IQ0 TIMER INTERRUPT
				if(strlen(buff)>0 && strcmp(buff, "timer") == 0)
		 		{
					asm volatile("sti");
					//clear_screen();
		 			init_timer(50);
		 		}
				// spacebar test
				if(strlen(buff)>0 && strcmp(buff, " ") == 0)
					printF("\nSpacebar anyone");
				
				// Display files
				if(strlen(buff)>0 && strcmp(buff, "ls") == 0)
					display_file_names();

				// STILL UNDER CONSTRUCTION !!!
				// create a new file from the shell
				if(strlen(buff)>0 && strcmp(buff, "new file") == 0)
		 		{
					printF("\nplease enter the name of the file\n");
					char *word;
					//*word = getS();
					//strcpy(&word, getS());
					//printF("\nCreated %s\n",getS());
					if((create_file(getS())) == 0 ){
						printF("\nfile created\n");
					}

				}

				// Display intros
				if(strlen(buff)>0 && strcmp(buff, "intro") == 0){
					clear_screen();
					printF("%s",os_development_passage);
				}
				// Display principles of development
				if(strlen(buff)>0 && strcmp(buff, "principles") == 0){
					clear_screen();
					printF("%s",Design_Principles_of_Operating_Systems);
				}
				// Display OS_Architecture types
				if(strlen(buff)>0 && strcmp(buff, "architecture") == 0){
					clear_screen();
					printF("%s",OS_Architecture);
				}
				// Display Key_Components_of_an_Operating_System
				if(strlen(buff)>0 && strcmp(buff, "components") == 0){
					clear_screen();
					printF("%s",Key_Components_of_an_Operating_System);
				}
				// Display Development_Process_of_an_Operating_System
				if(strlen(buff)>0 && strcmp(buff, "development process") == 0){
					clear_screen();
					printF("%s",Development_Process_of_an_Operating_System);
				}
				// Display Challenges_in_OS_Development
				if(strlen(buff)>0 && strcmp(buff, "challenges in os development") == 0){
					clear_screen();
					printF("%s",Challenges_in_OS_Development);
				}
				// Display Future_Trends_in_OS_Development
				if(strlen(buff)>0 && strcmp(buff, "future trends") == 0){
					clear_screen();
					printF("%s",Future_Trends_in_OS_Development);
				}


				//clears the buffer and prints the prompt
		 		printprompt(); 
				//kprint(buff);//test to see buffer
				///another kbd testing tool
				// char *typed;
				// hex_to_ascii(buff,typed); // or byte 
				// kprint("typed this:");
				// kprint(typed);
				////
		 		memset(&buff[0],0,sizeof(buff));
		 		break;
		 	}
		 	else{
				// This is linked up to the kbd for mapping the keys
		 		char c = normalmap[byte];
		 		char* s;
				if (c == '\b'){
					// moves the cursor back 2 steps to remove the last character
					backspace();
					// Sets the last character to '\0'
					Kbackspace(buff);
					
					break;
				}
				if (c == '\t'){
					kprint(" ");
					int len = strlen(s);
					buff[len] = " ";
				}
				else{
					s = ctos(s, c);
		 			kprint(s);
		 			strcpy(&buff[strlen(buff)], s);
				}	
		 	}
		 }
			
	}
	return 0;
}
