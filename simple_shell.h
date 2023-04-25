#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.H>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcnt1.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* This points to arrays of pointers to strings called the "environment" */

extern char **environ;


/**
 * struct data - the struct is a function that contains all relevant data on runtime
 * @av: argument vector
 * @input: the line of command written by the user
 * @args: command line tokens
 * @status: last status of the shell
 * @counter: function that counts the lines
 * @_environ: the environment of a variable
 * @pid: The ID of a particular process of shell
 */

typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;


/**
 * struct sep_list_s - single linked list
 * @seperator: ; | &
 * @next: next node
 * Description: single linked list to store seperators
 */

typedef struct sep_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */

typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function
 */

typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;


/* get_prompt_1.c */

void get_sigint(int prompt);

#endif
