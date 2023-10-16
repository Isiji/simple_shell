#ifndef SHELL_H
#define SHELL_H

#define MAX_INPUT_SIZE 1024
#define BUFPATH_LEN 1024
#define BUFFER_SIZE 1024
#define INITIAL_LINE_SIZE 128
#define MAX_PATH_LENGTH 1024

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>

void my_env(void);
int tokenization(char *str, char *args[], int max_arguments);
void blizz(const char *format, ...);
void simple_prompt();
void execution(char *message, const char *pathenv);
void *get_command(char *command, size_t size);
int search_command(const char *command, const char *pathenv, char *bufpath, size_t bufpath_len);
void our_exit(int status);
int convert_atoi(const char *str);
void my_exit(int status);
char *the_strncpy(char *dest, const char *source, size_t n);
char *my_strtok(char *str, const char *delim);
int the_delimiter(char c, const char *delim);
char *the_strdup(const char *str);
size_t the_strlen(const char *str);
char our_strcat(char *dest, const char *src);
int the_strcmp(const char *s1, const char *s2);
void changeDirectory(const char *path);
void handleCdCommand(char *args[], int argc);
void handleExitCommand(char *args[], int argc);
void executeExternalCommand(char *args[], int argc, char *envp[],
		char *bufpath, pid_t baby_pid, const char *pathenv);
void handleUnsetenvCommand(char *args[], int argc);
void handleSetenvCommand(char *args[], int argc);
int tokenizeCommands(char *message, char *commands[], int max_commands);
char *intToString(int value);
char *replaceVariables(char *command);
void replaceExitStatus(char *args[], int argc, int exitStatus);
void replaceProcessID(char *args[], int argc);
void reconstructCommand(char *replacedCommand, char *args[], int argc);
void parse_and_store_path(char *path, char *path_directories[]);
int our_itoa(int n, char *str);
void our_strrev(char *str);
ssize_t my_getline(char **lineptr, size_t *n, int fd);
char *trim_whitespace(char *str);
int the_isspace(char c);
ssize_t my_write(int fd, const char *str, size_t len);
char *my_itoa(int value, char *str);

#endif
