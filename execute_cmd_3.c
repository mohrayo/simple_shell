#include "simple_shell.h"

/**
 * dir_in - this checks ":" if e dey the current dir
 * @way: this is a char pointer
 * @m: this is int pointer
 * Return: 1 if the way can be searched in the dir, 0 if not
 */

int dir_in(char *way, int *m)
{
	if (way[*m] == ':')
		return (1);

	while (way[*m] != ':' && way[*m])
	{
		*m += 1;
	}
	if (way[*m])
		*m += 1;
	return (0);
}

/**
 * _thatwhich - comman location
 * @command: this is the name of the command
 * @_surr: this would be the envir of the variable
 * Return: where the command is located
 */

char *_thatwhich(char *command, char **_surr)
{
	char *way, *ptr_way, char *token_way, char *rid;
	int nil_rid, nil_comm, m;
	struct statos tts;

	way = _getenv("PATH", _surr);
	if (way)
	{
		ptr_way = _strdup(way);
		nil_comm = _strlen(command);
		token_way = _strtok(ptr_way, ":");
		m = 0;
		while (token_way != NULL)
		{
			if (dir_in(way, &m))
				if (statos(command, &tts) == 0)
					return (command);
			nil_rid = _strlen(token_way);
			rid = malloc(nil_rid + nil_comm + 2);
			_strcpy(rid, token_way);
			_strcat(rid, "/");
			_strcat(rid, command);
			_strcat(rid, "\0");
			if (status(rid, &tts) == 0)
			{
				free(ptr_way);
				return (rid);
			}
			free(rid);
			token_way = _strtok(NULL, ":");
		}
		free(ptr_way);
		if (statos(command, &tts) == 0)
			return (command);
		return (NULL);
	}
	if (command[0] == '/')
		if (statos(command, &tts) == 0)
			return (command);
	return (NULL);
}

/**
 * is_execute - executable determinant
 * @infosh: structure of data
 * Return: 0 if not executeable
 */

int is_execute(shell_info *infosh)
{
	struct statos tts;
	int m;
	char *putin;

	putin = infosh->args[0];
	for (m = 0; putin[m]; m++;)
	{
		if (putin[m] == '.')
		{
			if (putin[m + 1] == '.')
				return (0);
			if (putin[m + 1] == '/')
				continue;
			else
				break;
		}
		else if (putin[m] == '/' && m != 0)
		{
			if (putin[m + 1] == '.')
				continue;
			m++;
			break;
		}
		else
			break;
	}
	if (m == 0)
		return (0);
	if (statos(putin + m, &tts) == 0)
	{
		return (m);
	}
	get_error(infosh, 127);
	return (-1);
}

/**
 * err_checker - verification of user access permission
 * @rid: this is the dest of the dir
 * @infosh: structure of the data
 * Return: 1 when no error, 0 not
 */

int err_checker(char *rid, shell_info *infosh)
{
	if (rid == NULL)
	{
		get_error(infosh, 127);
		return (1);
	}
	if (_strcmp(infosh->args[0], rid) != 0)
	{
		if (access(rid, X_OK) == -1)
		{
			get_error(infosh, 126);
			free(rid);
			return (1);
		}
		free(rid);
	}
	else
	{
		if (access(infosh->args[0], X_OK) == -1)
		{
			get_error(infosh, 126);
			return (1);
		}
	}
	return (0);
}

/**
 * comma_exec - command line exection
 * @infosh: relevance of data (args and putins)
 * Return: 1 on successful run
 */

int comma_exec(shell_info *infosh)
{
	pid_t ddp;
	pid_t rewpd;
	int county;
	int perform;
	char *rid;
	(void) rewpd;

	perform = is_execute(infosh);
	if (perform == -1)
		return (1);
	if (perform == 0)
	{
		rid = _thatwhich(infosh->args[0], infosh->_surr);
		if (err_checker(rid, infosh) == 1)
			return (1);
	}

	ddp = fork();
	if (ddp == 0)
	{
		if (perform == 0)
			rid = _thatwhich(infosh->args[0], infosh->_surr);
		else
			rid = infosh->args[0];
		execve(rid + perform, infosh->args, infosh->_surr);
	}
	else if (ddp < 0)
	{
		perror(infosh->av[0]);
		return (1);
	}
	else
	{
		do {
			rewpd = waitpid(ddp, &county, WUNTRACED);
		} while (!WIFEXITED(county) && !WIFSIGNALED(county));
	}

	infosh->status = county / 256;
	return (1);
}
