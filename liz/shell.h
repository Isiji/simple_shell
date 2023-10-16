#ifndef _SHELL_H_
#define _SHELL_H_

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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_num() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passdata - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readdt: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passdata
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readdt;
	int histcount;
} data_t;

#define DATA_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(data_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(data_t *data, char **av);
int find_builtin(data_t *data);
void find_cmd(data_t *data);
void fork_cmd(data_t *data);

/* toem_parser.c */
int the_cmd(data_t *data, char *path);
char *dup_chars(char *path_s, int start, int stop);
char *find_path(data_t *data, char *path_s, char *cmd);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void the_eputs(char *str);
int the_eputchar(char k);
int the_putdt(char c, int dt);
int the_putsdt(char *str, int dt);

/* toem_string.c */
int the_strlen(char *str);
int the_strcmp(char *str1, char *str2);
char *our_node(const char *srch, const char *sub_srch);
char *the_strcat(char *dest, char *src);

/* toem_string1.c */
char *the_strcpy(char *dest, char *src);
char *the_strdup(const char *str);
int the_putchar(char c);
void the_puts(char *str);

/* toem_exits.c */
char *the_strncpy(char *dest, char *src, int t);
char *the_strncat(char *dest, char *src, int t);
char *the_strchr(char *str, char c);

/* toem_tokenizer.c */
char **str_wrd(char *str, char *d);
char **str_wrd1(char *str, char d);

/* toem_realloc.c */
char *the_memset(char *p, char b, unsigned int num);
void free_str(char **sstr);
void *the_realloc(void *ptr, unsigned int prev_size, unsigned int new_size);

/* toem_memory.c */
int free_p(void **p);

/* toem_atoi.c */
int inter(data_t *data);
int the_delim(char c, char *delim);
int the_alph(int j);
int the_atoi(char *s);

/* toem_errors1.c */
int the_errtoi(char *c);
void prt_err(data_t *data char *str);
int print_d(int entry, int dt);
char *convert_num(long int num, int base, int flags);
void rem_comments(char *buf);

/* toem_builtin.c */
int the_exit(data_t *data);
int the_cd(data_t *data);
int the_help(data_t *data);

/* toem_builtin2.c */
int the_history(data_t *data);
int unset_alias(data_t *data, char *str);
int set_alias(data_t *data, char *str);
int print_alias(list_t *node);
int the_alias(data_t *data);

/*toem_getline.c */
ssize_t entry_buf(data_t *data, char **buf, size_t *len);
ssize_t the_input(data_t *data);
int the_getline(data_t *data, char **ptr, size_t *length);
void sigint(__attribute__((unused))int sig_count);

/* toem_getinfo.c */
void clear_data(data_t *data);
void set_data(data_t *data, char **av);
void free_data(data_t *data, int all);

/* toem_environ.c */
char *the_getenv(data_t *data, const char *name);
int the_env(data_t *data);
int the_setenvr(data_t *data);
int the_unsetenvr(data_t *data);
int pop_envlist(data_t *data);

/* toem_getenv.c */
char **get_env(data_t *data);
int the_unsetenv(data_t *data, char *var);
int the_setenv(data_t *data, char *var, char *value);

/* toem_history.c */
char *the_hist(data_t *data);
int write_history(data_t *data);
int read_history(data_t *data);
int build_history(data_t *data, char *buf, int linecount);
int renumber_history(data_t *data);

/* toem_lists.c */
list_t *the_node(list_t **head, const char *str, int num);
list_t *the_node_end(list_t **head, const char *str, int num);
size_t the_list_str(const list_t *head);
int delete_node(list_t **h, unsigned int index);
void free_node(list_t **head_p);

/* toem_lists1.c */
size_t list_len(const list_t *h);
char **list_str(list_t *h);
size_t print_list(const list_t *h);
list_t *starts_with(list_t *node, char *pre char n);
ssize_t node_index(list_t *h, list_t *node);

/* toem_vars.c */
int the_chain(data_t *data, char *buf, size_t *d);
void check_chain(data_t *data, char *buf, size_t *d, size_t i, size_t len);
int rep_alias(data_t *data);
int replace_vars(data_t *data);
int replace_string(char **prev, char *new);

#endif
