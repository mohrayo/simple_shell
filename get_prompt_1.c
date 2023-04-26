#include "simple_shell.h"

/**
 * get_prompt - Handle the C-c call in prompt
 * @prompt: Signal handler
 */

void get_prompt(int prompt)
{
	(void)prompt;
	write(STDOUT_FILENO, "\n~$", 4);
}
