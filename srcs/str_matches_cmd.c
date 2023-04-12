#include "../includes/minishell.h"


/*
TODO:
引数には単語だけ渡したほうがいい。
前後のスペースなどは除去する。コマンドがその単語だけか判断するために、
終端文字を判断材料にする。
例)
OK: cd
KO: cda
KO: cdbac
*/
void	line_matches_cmd(char *line)
{
	char	**cmd_line = NULL;
	t_token	*token;
	t_node	*node;

	token = tokenize(line);
	node =	parse(token);
	expand(node);
	// printf("%s\n", node->args->word);
	// printf("%s\n", node->args->next->word);
	// printf("%s\n", node->args->next->next->word);
	open_redir_file(node->redirects);
	do_redirect(node->redirects);
	cmd_line = token_list_to_array(node->args);
	cmd_line[0] = get_cmd_array(ft_strtrim(cmd_line[0], " "));

	if (cmd_line != NULL)
	{
		if (execve(cmd_line[0], cmd_line, environ) == -1)
		{
			// printf("\x1b[31mError: execve()\x1b[0m\n");
		}
		reset_redirect(node->redirects);
	}
	return ;
}
