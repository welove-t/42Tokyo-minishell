/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_bi_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:45:48 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/26 14:52:25 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
static int search_bi_cmd_helper(int argc,char **argv, t_environ *environ)
{
	int flag;
	//成功時:0,失敗時:-1
	flag = 0;
	if (strcmp(argv[0],"pwd") == 0)
		flag = bi_pwd();
	else if (strcmp(argv[0],"cd") == 0)
		flag = bi_cd(argv,argc);
	else if (strcmp(argv[0],"echo") == 0)
		flag = bi_echo(argv);
	else if (strcmp(argv[0],"env") == 0)
		flag = bi_env(argc, environ);
	else if (strcmp(argv[0],"exit") == 0)
		flag = bi_exit(argv);
	else if (strcmp(argv[0],"export") == 0)
		flag = bi_export(environ,argv,argc);
	else if (strcmp(argv[0],"unset") == 0)
		flag = bi_unset(environ,argv,argc);
	else
		return (1);
	return (flag);
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
	if (tmp_token->word == NULL)
		return (NULL);
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
int search_bi_cmd(t_node *node,t_environ *environ)
{
	int flag;
	char **argv;
	int argc;
	flag = 0;

	(void)node;
	argv = string_to_array(&argc ,node->args);
	if (argv == NULL)
		return (0);
	flag = search_bi_cmd_helper(argc,argv,environ);
	// if (flag == 0)
	// 	printf("\x1b[32mBuilt in commandが呼ばれた(%d)\x1b[0m\n",flag);
	// else
	// 	printf("\x1b[31mBuilt in commandが呼ばれてない(%d)\x1b[0m\n",flag);
	return (flag);
}