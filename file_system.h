#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#define MAX_FILES 16
#define MAX_NAME_LEGTH 32
#define MAX_FILE_SIZE 1024

#include <stddef.h>

typedef unsigned long size_t;

typedef struct{
	char name [MAX_NAME_LEGTH];
	int is_directory;
	char content[MAX_FILE_SIZE];
	int parent;                      // Parent directory index

} File;
typedef struct{
	File files[MAX_FILES];
	int file_count;
} FileSystem;


void init_fs();
int create_directory(const char *name);
int create_file(const char *name);
void list_directory();
File *find_file(const char *name);
void process_command(const char *cmd, int *debug_mode, char command_history[][100], int command_history_count);
void print_command(const char *cmd, int debug_mode);

#endif
