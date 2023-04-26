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
	int t;

	for (t = 0; nsurr[t] != "="; t++)
	{
		if (nsurr[t] != name[t])
		{
			if (nsurr[t] != name[t])
			{
				return (0);
			}
		}

		return (t + 1);
	}
}

/**
 * _getenvar - get environ variable
 * @name: name of environ variable
 * @_surr: environ variable
 *
 * Return: value of environ, return NULL
 */

char *_getenvar(const char *name, char **_surr)
{
	char *ptr_surr;
	int m, vom;

	ptr_surr = NULL;
	vom = 0;

	for (m = 0; _surr[m]; m++;)
	{
		vom = comp_surr_name(_surr[m], name);
		if (vom)
		{
			ptr_surr = _surr[m];
			break;
		}
	}

	return (ptr_surr + vom);
}

/**
 * _suurr - prints environ variables
 *
 * @infosh: data relevant
 * Return: 1 on success.
 */

int _suurr(shell_info *infosh)
{
	int t, v;

	for (t = 0; infosh->_surr[t]; t++)
	{
		for (v = 0; infosh->_surr[t][v]; v++)
			;
		write(STDOUT_FILENO, infosh->_surr[t], v);
		write(STDOUT_FILENO, "\n", 1);
	}
	infosh->status = 0;

	return (1);
}
