/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 13:38:03 by terabu            #+#    #+#             */
/*   Updated: 2023/05/04 14:45:11 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	get_node_cnt(t_node *node);

void	execution(t_node *node, t_environ *environ)
{
	size_t	cnt_node;
	pid_t	pid;
	int		wstatus;

	wstatus = 0;
	cnt_node = get_node_cnt(node);
	if (cnt_node <= 1)
	{
		/*
		node->args->wordの中にcdなどのコマンドが入っている。
		fork()前にbuiltinか確認する。builtinだったら、forkしない
		*/
		//設定したビルトインコマンドがあったら、0が返ってくる
		if (search_bi_cmd(node, environ) != 1)
			return ;
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid < 0)
			fatal_error("fork");
		else if (pid == 0)
			exec_cmd(node, environ);
		else
			wait(&wstatus);
	}
	else
	{
		pipex(node, cnt_node, environ);
		waitpid_pipex(node, &wstatus);
	}
	finalize(node, wstatus);
}

// void	printf_argv(char **argv)
// {
// 	for (int i = 0; argv[i]; i++)
// 	{
// 		dprintf(2, "argv[%d]:%s\n", i, argv[i]);
// 	}
// }

// void	print_env(void)
// {
// 	t_environ	*tmp;

// 	tmp = g_global.mini_environ;
// 	while (tmp)
// 	{
// 		dprintf(2, "mini-env:")
// 		tmp = tmp->next;
// 	}
// }

char	**env_list_to_array(t_environ *environ)
{
	t_environ	*tmp_env;
	size_t		i;
	char		**list_env;
	char		*tmp;

	tmp_env = environ;
	list_env = ft_calloc(get_environ_cnt(tmp_env) + 1, sizeof(char *));
	if (!list_env)
		fatal_error("calloc");
	i = 0;
	while (tmp_env)
	{
		tmp = ft_strjoin(tmp_env->name, "=");
		list_env[i] = ft_strjoin(tmp, tmp_env->value);
		tmp_env = tmp_env->next;
		i++;
	}
	return (list_env);
}

void	exec_cmd(t_node *node, t_environ *mini_environ)
{
	char	**argv;

	redirection(node->redirects,mini_environ);
	if (g_global.flg_redir != 0)
		exit(EXIT_FAILURE);
	argv = token_list_to_array(node->args);
	// printf_argv(argv);
	// dprintf(2, "status:%d\n", g_global.status);
	// printf_argv(env_list_to_array(mini_environ));
	argv[0] = get_cmd_array(argv[0]);
	// if (g_global.status != 1)
	// {
		if (argv[0] != NULL)
		{
			//ctrl-c: 130
			signal(SIGINT, signal_handler_waiting_input);
			//ctrl-\: 131
			signal(SIGQUIT, signal_handler_waiting_input);
			if (execve(argv[0], argv, env_list_to_array(mini_environ)) == -1)
				error_exit(argv[0]);

		}
		else
			error_cmd(node->args->word);
	// }
	// reset_redirect(node->redirects);
}

size_t	get_environ_cnt(t_environ *node)
{
	size_t	cnt;

	cnt = 0;
	while (node != NULL)
	{
		cnt++;
		node = node->next;
	}
	return (cnt);
}

size_t	get_node_cnt(t_node *node)
{
	size_t	cnt;

	cnt = 0;
	while (node != NULL)
	{
		cnt++;
		node = node->next;
	}
	return (cnt);
}
