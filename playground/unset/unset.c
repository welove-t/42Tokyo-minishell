#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <unistd.h>

typedef struct s_environ
{
	char				*name;
	char				*value;
	struct s_environ	*next;
}						t_environ;

typedef struct s_envinfo
{
	//先頭ノード
	t_environ			*head;
}						t_envinfo;


int	is_valid_param_name(char *str)
{
	if (ft_strchr(str, '=') != NULL)
	{
		printf("unset: %s: invalid parameter name\n", str);
		return (0);
	}
	return (1);
}

t_environ	*find_variable(t_environ *environ, char *str)
{
	t_environ	*tmp;

	tmp = environ;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, str) == 0)
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	remove_variable(t_environ *environ, t_environ *var)
{
	while (environ != NULL)
	{
		if (environ->next->name == var->name)
		{
			environ->next = environ->next->next;
			break ;
		}
		environ = environ->next;
	}
}

void	bi_unset(t_environ *environ, char *str)
{
	t_environ	*var;

	if (!is_valid_param_name(str))
	{
		return ;
	}
	var = find_variable(environ, str);
	if (var == NULL)
	{
		return ;
	}
	remove_variable(environ, var);
	return ;
}


static void	bi_env(t_environ *environ)
{
	t_environ	*tmp;

	tmp = environ;
	// 環境変数を1行ずつ出力
	while (tmp != NULL)
	{
		printf("%s", tmp->name);
		if (tmp->value != NULL)
			printf("=%s", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
}

int	first_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	latter_strlen(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (-1);
	i++;
	while (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
	{
		i++;
		res++;
	}
	return (res);
}

char	*make_name(char *str)
{
	char	*name;
	int		fir_len;

	fir_len = first_strlen(str);
	name = (char *)malloc(fir_len + 1);
	strncpy(name, str, fir_len);
	name[fir_len] = '\0';
	return (name);
}

char	*make_value(char *str)
{
	char	*value;
	int		lat_len;
	int		fir_len;

	fir_len = first_strlen(str);
	lat_len = latter_strlen(str);
	if (lat_len == -1)
		return (NULL);
	value = (char *)malloc(lat_len + 1);
	strncpy(value, str + fir_len + 1, lat_len);
	value[lat_len] = '\0';
	return (value);
}

//新たにノードを作る
static t_environ	*environ_node_new(char *name, char *value)
{
	t_environ	*new;

	new = (t_environ *)malloc(sizeof(t_environ));
	if (new == NULL)
		return (NULL);
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

extern char				**environ;
static t_environ	*init_environ_list()
{
	int			i;
	int			j;
	int			n;
	char		*name;
	char		*value;
	char		**tmp;
	t_environ	*env_list;
	t_envinfo	*env_info;
	int			flag;
	t_environ	*new;

	i = 0;
	flag = 0;
	//環境変数environの値を直接変更したくないため
	tmp = environ;
	env_list = NULL;
	env_info = (t_envinfo *)malloc(sizeof(t_envinfo));
	env_info->head = NULL;
	//環境変数を1行ずつ出力
	while (tmp[i] != NULL)
	{
		j = 0;
		n = 0;
		name = make_name(tmp[i]);
		value = make_value(tmp[i]);
		new = environ_node_new(name, value);
		new->name = name;
		new->value = value;
		if (flag == 0)
		{
			env_list = new;
			env_info->head = env_list;
			flag = 1;
		}
		else
		{
			env_list->next = new;
			env_list = env_list->next;
		}
		i++;
	}
	env_list = NULL;
	env_list = env_info->head;
	return (env_list);
}

int	main(int argc, char **argv)
{
	t_environ *environ;
	environ = init_environ_list();
	if (argc == 1)
	{
		return (1);
	}
	bi_unset(environ, argv[1]);
	bi_env(environ);
	return (0);
}