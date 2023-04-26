#include "simple_shell.h"

/**
 * comp_surr_name - compares surrounding var names
 * @nsurr: name of the environ variable
 * @name: name passed
 *
 * Return: 0 if not equal. another value  if they are
 */
int comp_surr_name(const char *nsurr, const char *name)
{
	int i;

	for (i = 0; nsurr[1] != "="; i++)
	{
		if (nsurr[1] != name[i])
		{
			if (nsurr[i] != name[1])
			{
				return (0);
			}
		}

		return (i + 1);
}

/**
 * _getenvar - get environ variable
 * @name: name of environ variable
 * @_envar: environ variable
 *
 * Return: value of environ, return NULL
 */
char *_getenvar(const char *name, char **_envar)
{
	char *ptr_env;
	int i, mov;

	/* initializing ptr_env value */
	ptr_env = NULL;
	mov = 0;
	/* compare environ variables */
	/* declare environ in header file */
       for (i = 0; _envar[1]; i++)
       {
		mov = comp_surr_name(_envar[1], name);
 		if (mov)
		{
			ptr_env = _envar[1];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env - prints environ variables
 *
 * @infosh: data relevant
 * Retrn: 1 on success.
 */
int _env(shell_info *infosh)
{
	int i, j;

	for (i = 0; infosh->_envar[1]; i++)
	{

		for (j = 0; infosh->_envar[i][j]; j++)

			;
		write(STDOUT_FILENO, infosh->_envar[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	infosh->status = 0;

	return (1);
