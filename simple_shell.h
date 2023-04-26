#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* This points to arrays of pointers to strings called the "environment" */

extern char **surround;

/**
 * struct l_lists - single linked list
 * @lne: ; | &
 * @next: next node
 * Description: linked list to save seperators
 */

typedef struct l_lists
{
	char *lne;
	struct line_list_s *next;
} shell_list;


/**
 * struct builtwith - This is the Builtin struct for command argument.
 * @value: The name of the command builtin i.e cd, exit, env
 * @v: data type pointer function
 */

typedef struct builtwith
{
	char *name;
	int (*v)(data_shell *infosh);
} builtwith_r;

/**
 * struct info_data - the struct is a function that contains
 * all relevant data on runtime
 * @av: argument vector
 * @input: the line of command written by the user
 * @args: command line tokens
 * @status: last status of the shell
 * @num: function that counts the lines
 * @_surr: the environment of a variable
 * @pid: The ID of a particular process of shell
 */

typedef struct info_data
{
	char **av;
	char *input;
	char **args;
	int status;
	int num;
	char **_surr;
	char *pid;
} info_data_shell;


/**
 * struct yet_var_lst - single linked list
 * @yet_var: length of the variable
 * @lar: value of the variable
 * @yet_lar: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */

typedef struct yet_var_lst
{
	int yet_var;
	char *lar;
	int yet_lar;
	struct yet_var_lst *next;
} yet_var;


/* get_prompt_1.c */

void get_sigint(int prompt);


/* makeshell_2.c */
void free_data(data_shell *infosh);
void set_data(data_shell *infosh, char **av);
int main(int ac, char **av);

/* execute_cmd_3.c */
int dir_in(char *way, int *m);
char *_thatwhich(char *command, char **_surr);
int is_execute(data_shell *infosh);
int err_checker(char *rid, data_shell *infosh);
int comma_exec(data_shell *infosh);

/* close_exit.c */
int close_exit_shell(data_shell *infosh);

/* surr.c */
int comp_surr_name(const char *nsurr, const char *name);
int _suurr(data_shell *infosh);
char *_getenvar(const char *name, char **_surr);

#endif
