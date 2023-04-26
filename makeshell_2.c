#include "simple_shell.c"

/**
 * empty_data - this function frees up a data structure
 * @infosh: this is the data structure
 * Return: null
 */

void empty_data(shell_info *infosh)
{
	unsigned int fil;

	for (fil = 0; infosh->_surr[fil]; fil++)
	{
		free(infosh->_surr[fil]);
	}

	free(infosh->_surr);
	free(infosh->pid);
}

/**
 * assign_data - initialize data structure
 * @infosh: this is the data structure
 * @av: argument vector
 */

void assign_data(shell_info *infosh, char **av)
{
	unsigned int fil;

	infosh->av = av;
	infosh->input = NULL;
	infosh->args = NULL;
	infosh->status = 0;
	infosh->num = 1;

	for (fil = 0; surround[fil]; fil++)
		;

	infosh->_surr = malloc(sizeof(char *) * (fil + 1));

	for (fil = 0; surround[fil]; fil++)
	{
		infosh->_surr[fil] = _strdup(surround[fil]);
	}

	infosh->_surr[fil] = NULL;
	infosh->pid = aux_itoa(getpid());
}

/**
 * main - entering the value
 * @ac: counting the argument
 * @av: the vector of an argument
 * Return: this returns 0 on success
 */

int main(int ac, char **av)
{
	shell_info infosh;
	(void) ac;

	prompt(SIGNIT, get_sigint);
	assign_data(&infosh, av);
	looping_shell(&infosh);
	empty_data(&infosh);
	if (infosh.status < 0)
		return (255);
	return (infosh.status);
}
