#include "simple_shell.h"

/**
 * close_exit_shell - leaves the shell
 *
 * @infosh: data relevance (status and args)
 * Return: 0 on success..
 */
int close_exit_shell(shell_info *infosh)
{
	unsigned int ustatus;
	int digits_;
	int length_strng;
	int max_num;

	if (infosh->args[1] != NULL)
	{
		ustatus = -atoi(infosh->args[1]);
		digits_ = digits_(infosh->args[1]);
		length_strng = length_strng(infosh->args[1]);
		max_num = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || length_strng > 10 || big_number)
		{
			get_error(infosh, 2);
			infosh->status = 2;
			return (1);
		}
		infosh->status = (ustatus % 256);
	}
	return (0);
}
