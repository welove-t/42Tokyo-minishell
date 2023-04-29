/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_bi_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:45:48 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/29 18:02:14 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	check_bi(char *cmd)
{
	if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (true);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	else if (ft_strcmp(cmd, "env") == 0)
		return (true);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	else if (ft_strcmp(cmd, "export") == 0)
		return (true);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (true);
	else
		return (false);
}

static int	search_bi_cmd_helper(int argc, char **argv, t_environ *environ)
{
	int	flag;

	flag = 0;
	if (ft_strcmp(argv[0], "pwd") == 0)
		flag = bi_pwd();
	else if (ft_strcmp(argv[0], "cd") == 0)
		flag = bi_cd(argv, argc);
	else if (ft_strcmp(argv[0], "echo") == 0)
		flag = bi_echo(argv);
	else if (ft_strcmp(argv[0], "env") == 0)
		flag = bi_env(argc, environ);
	else if (ft_strcmp(argv[0], "exit") == 0)
		flag = bi_exit(argv);
	else if (ft_strcmp(argv[0], "export") == 0)
		flag = bi_export(environ, argv, argc);
	else if (ft_strcmp(argv[0], "unset") == 0)
		flag = bi_unset(environ, argv, argc);
	else
		return (1);
	return (flag);
}

// int	get_args_cnt(t_token *token)
// {
// 	int		cnt;
// 	t_token	*tmp_token;

// 	cnt = 0;
// 	tmp_token = token;
// 	while (tmp_token->next != NULL)
// 	{
// 		tmp_token = tmp_token->next;
// 		cnt++;
// 	}
// 	return (cnt);
// }

// char	**string_to_array(int *argc, t_token *token)
// {
// 	t_token	*tmp_token;
// 	char	**argv;
// 	int		i;

// 	tmp_token = token;
// 	if (tmp_token->word == NULL)
// 		return (NULL);
// 	*argc = get_args_cnt(tmp_token);
// 	argv = malloc(sizeof(char *) * (*argc + 1));
// 	if (argv == NULL)
// 		fatal_error("malloc error");
// 	i = 0;
// 	while (tmp_token->word != NULL)
// 	{
// 		// tmp_token->wordをdupして、argvをに代入
// 		argv[i] = ft_strdup(tmp_token->word);
// 		tmp_token = tmp_token->next;
// 		i++;
// 	}
// 	argv[i] = NULL;
// 	return (argv);
// }

int	search_bi_cmd(t_node *node, t_environ *environ)
{
	int		flag;
	char	**argv;

	flag = 0;
	argv = token_list_to_array(node->args);
	if (argv == NULL)
		return (0);
	if (argv[0] == NULL)
	{
		free_argv(argv);
		return (0);
	}
	if (check_bi(argv[0]))
	{
		redirection(node->redirects);
		if (g_global.flg_redir == 1)
		{
			free_argv(argv);
			return (-1);
		}
		flag = search_bi_cmd_helper((int)get_token_count(node->args), argv, environ);
		reset_redirect(node->redirects);
	}
	else
		flag = 1;
	free_argv(argv);
	return (flag);
}
