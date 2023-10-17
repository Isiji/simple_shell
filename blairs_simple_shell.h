
#ifndef _BLAIRS_SIMPLE_SHELL_H_
#define _BLAIRS_SIMPLE_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>
/* Read/Write Buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1
#define MAX_LENGTH 1024

/* Command Chaining */
#define NORMAL_COMMAND 0
#define OR_COMMAND 1
#define AND_COMMAND 2
#define CHAIN_COMMAND 3

/* Number Conversion */
#define CONVERT_TO_LOWERCASE 1
#define CONVERT_TO_UNSIGNED 2

/* System getline Usage */
#define USE_SYSTEM_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE ".blairs_shell_history"
#define MAX_HISTORY_ENTRIES 4096

extern char **environ;

/**
 * struct StringList - this is a singly linked list
 * @number: the number field
 * @str: string to be passed
 * @next: points to next node
 */

typedef struct StringList
{
	int number;
	char *str;
	struct StringList *next;
} StringList;

/**
 * struct CommandData - contains arguments to pass into a function
 * @arguments: a string containing arguments
 * @argv: array of arguments
 * @path: a path for the current command
 * @argument_count: argument count
 * @error_number: error for exit
 * @linecount_flag: counts lines of input
 * @line_counter: counts error in lines
 * @program_name: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @environment_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @command_buffer: address of pointer to cmd_buf, on if chaining
 * @command_buffer_type: CMD_type ||, &&, ;
 * @read_descriptor: the dt from which to read line input
 * @history_count: the history line number count
 */
typedef struct CommandData
{
	char *arguments;
	char **argv;
	char *path;
	int argument_count;
	unsigned int line_counter;
	int error_number;
	int linecount_flag;
	char *program_name;
	StringList *env;
	StringList *history;
	StringList *alias;
	char **environ;
	int environment_changed;
	int status;
	char **command_buffer;
	int command_buffer_type;
	int read_descriptor;
	int history_count;
}
CommandData;

#define COMMAND_DATA_INIT \
{ NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, \
	NULL, 0, 0, 0}

/**
 * struct BuiltinCommand - contains a build in string
 * @type: the built in command flag
 * @function: the function
 */
typedef struct BuiltinCommand
{
	char *type;
	int (*function)(CommandData *);
} BuiltinCommandTable;

/* Shell Functions */
int main_shell(CommandData *data, char **arguments);
int find_builtin(CommandData *data);
void find_command(CommandData *data);
void fork_command(CommandData *data);

/* Parser Functions */
int handle_command(CommandData *data, char *path);
char *duplicate_chars(char *source, int start, int stop);
char *find_command_path(CommandData *data, char *path_string, char *command);

/* Loop Functions */
int shell_loop(CommandData *data, char **arguments);

/* Error Handling Functions */
void print_error_message(char *message);
int print_error_character(char character);
int print_integer(int number, int descriptor);
int print_string_descriptor(char *string, int descriptor);

/* String Functions */
int string_length(const char *string);
int compare_strings(char *string1, char *string2);
char *string_starts_with(const char *search, const char *substring);
char *concatenate_strings(char *destination, char *source);

/* String Functions (Part 2) */
char *copy_string(char *destination, const char *source);
char *duplicate_string(const char *string);
void print_string(char *string);
int print_character(char character);

/* Exit Functions */
char *concatenate_strings_with_length
(char *destination, char *source, int length);
char *find_character_in_string(char *string, char character);
char *copy_string_with_length(char *destination,
		const char *source, int max_length);

/* Tokenization Functions */
char **split_string(char *string, char *delimiter);
char **split_string_version2(char *string, char delimiter);

/* Realloc Functions */
char *fill_memory_with_character(char *pointer, char character,
		unsigned int number);
void free_string_array(char **strings);
void *reallocate_memory(void *pointer, unsigned int previous_size,
		unsigned int new_size);

/* Memory Management Functions */
int free_pointer(void **pointer);
void free_environment(StringList *head);

/* Atoi Functions */
int interpret(CommandData *data);
int is_delimiter(char character, char *delimiter_set);
int is_alphabetic(int character);
int atoi_custom(char *string);

/* Error Handling Functions (Part 2) */
int custom_atoi(char *string);
void print_error_message_v2(CommandData *data, char *message);
int print_integer_v2(int number, int descriptor);
char *convert_integer_to_string(long int number, int lowercase_flag,
		int unsigned_flag);
void remove_comments_from_string(char *string);

/* Builtin Commands */
int execute_exit(CommandData *data);
int execute_cd(CommandData *data);
int execute_help(CommandData *data);
bool startsWith(const char *str, const char *prefix);


/* Builtin Commands (Part 2) */
int execute_history(CommandData *data);
int remove_alias(CommandData *data, char *string);
int execute_alias(CommandData *data);
/* Custom getline Functions */
ssize_t entry_buffer(CommandData *data, char **buffer, size_t *length);
ssize_t read_input(CommandData *data);
int custom_getline(CommandData *data, char **pointer, size_t *length);
void handle_interrupt_signal(__attribute__((unused))int signal_counter);

/* Environment Functions */
void clear_command_data(CommandData *data);
void set_command_data(CommandData *data, char **arguments);
void free_command_data(CommandData *data, int free_all);

/* Environment Functions (Part 2) */
char *get_environment_variable(CommandData *data, const char *variable_name);
int handle_environment(CommandData *data);
int set_environment_variable(CommandData *data);
int unset_environment_variable(CommandData *data);
int pop_environment_list(CommandData *data);

/* Get Environment Variable Functions */
char **get_custom_environment(CommandData *data);
int unset_custom_environment_variable(CommandData *data, char *variable);
int set_custom_environment_variable(CommandData *data, char *variable,
		char *value);

/* History Functions */
char *get_command_history(CommandData *data);
int write_command_history(CommandData *data);
int read_command_history(CommandData *data);
int build_command_history(CommandData *data, char *buffer, int linecount);
int renumber_command_history(CommandData *data);

/* Linked List Functions */
StringList *create_list_node(StringList **head,
		const char *str, int number);
StringList *create_list_node_at_end(StringList **head, const char *str,
		int number);
size_t print_list_strings(const StringList *head);
int delete_list_node(StringList **head_pointer, unsigned int index);
void free_list_node(StringList **head_pointer);

/* Linked List Functions (Part 2) */
size_t get_list_length(const StringList *head);
char **get_list_strings(StringList *head);
size_t print_linked_list(const StringList *head);
StringList *find_prefixed_node(StringList *node, char *prefix, char needle);
ssize_t find_node_index(StringList *head, StringList *node);

/* Variable Functions */
int is_command_chain(CommandData *data, char *input_string,
		size_t *current_index);
void check_command_chain(CommandData *data, char *input_string,
		size_t *current_index, size_t chain_start, size_t chain_end);
int replace_command_alias(CommandData *data);
int replace_command_variables(CommandData *data);
int replace_string(char **previous, char *new_string);

#endif

