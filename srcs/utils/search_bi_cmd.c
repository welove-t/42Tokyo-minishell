/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_bi_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:45:48 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/24 20:36:08 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int search_bi_cmd_helper(int argc,char **argv, t_environ *environ)
{
	// printf("argv[0] = %s\n",argv[0]);
	if (strcmp(argv[0],"pwd") == 0)
		bi_pwd();
	else if (strcmp(argv[0],"cd") == 0)
		bi_cd(argv);
	else if (strcmp(argv[0],"echo") == 0)
		bi_echo(argv);
	else if (strcmp(argv[0],"env") == 0)
		bi_env(environ);
	else if (strcmp(argv[0],"export") == 0)
		bi_export(environ,argv,argc);
	else if (strcmp(argv[0],"unset") == 0)
		bi_unset(environ,argv,argc);
	else
		return (0);
	return (1);
}

int get_args_cnt(t_token *token)
{
	int cnt;
	t_token *tmp_token;
	cnt = 0;
	tmp_token = token;
	while (tmp_token->next != NULL)
	{
		tmp_token = tmp_token->next;
		cnt++;
	}
	return (cnt);
}

char **string_to_array(int *argc, t_token *token)
{
	t_token *tmp_token;
	char **argv;
	int i;
	int cnt_args;

	tmp_token = token;
	cnt_args = get_args_cnt(tmp_token);
	*argc = cnt_args;
	argv = malloc(sizeof(char *)*(cnt_args + 1));
	if (argv == NULL)
		fatal_error("malloc error");
	i = 0;
	while(tmp_token->word != NULL)
	{
		argv[i] = tmp_token->word;
		tmp_token = tmp_token->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

int search_bi_cmd(t_node *node)
{
	int res;
	char **argv;
	int argc;
	t_environ *environ;

	environ = init_environ_list();
	argv = string_to_array(&argc ,node->args);
	res = search_bi_cmd_helper(argc,argv,environ);
	// if (res == 1)
	// 	printf("\x1b[32mBuilt in commandが呼ばれた(%d)\x1b[0m\n",res);
	// else
	// 	printf("\x1b[31mBuilt in commandが呼ばれてない(%d)\x1b[0m\n",res);
	return (res);
}