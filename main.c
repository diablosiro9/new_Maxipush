#include "../include/include.h"

unsigned int	starter_env(char *s)
{
	unsigned int	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

t_env *get_env(char **env)
{
    int i = 0;
    t_env *list = NULL;
    list = malloc(sizeof(t_env)* 100);
   
   while (env[i])
    {
        list[i].name = ft_strsub(env[i], 0, ft_strchr(env[i], '=') - env[i]);
        list[i].content =  ft_strsub(env[i], starter_env(env[i]), ft_strlen(env[i] -  (env[i] - ft_strchr(env[i], '='))));
		i++;
    }
    return (list);
}

t_list	*dquote_mod(char *tp, int flag)
{
	char	*stock = NULL;
	t_list	*temp = NULL;
	t_list	*cmd = NULL;
	// t_list	*save = cmd;
	(void)tp;
	(void)stock;

	cmd = ft_lstnew((void *)tp);
	while (42)
	{
	 	ft_putstr("dquote>");
        // stock = get_next_line(0);
		// printf("Yes or not\n");
		temp = ft_lstnew(get_next_line(0));
		stock = temp->content;
		ft_lstadd(&cmd, temp);
		if (flag == -1)
		{
			if (ft_strchr(stock, '\''))
				return (cmd);
		}
		if (flag == 0)
		{
			if (ft_strchr(stock, '"'))
				return (cmd);
		}
		// printf("history->content = %s\n", history->content);
	}
}

int	size_cmd(t_list	*cmd)
{
	int	i = 0;
	int	res = 0;
	char	*tp = NULL;

	while (cmd)
	{
		i = 0;
		tp = (char *)cmd->content;
		if (cmd->next == NULL)
			return (res);
		while (tp[i])
		{
			res++;
			i++;
		}
		cmd = cmd->next;
	}
	return (res);
}

int	checking_str(char *ref, char *find)
{
	int i = 0;
	int	j = 1;

	if (!ref || !find)
		return (0);
	while (ref[i])
	{
		if (ref[i] != find[j])
			return (0);
		i++;
		j++;
	}
	return (1);

}

void	search_env_content(t_env *env, t_list *name)
{
	int	i = 0;
	char	*str = (char *)name->content;
	while (env[i].name)
	{
		if (checking_str(env[i].name, str) == 1)
			name->content = env[i].content;
		i++;
	}
}

void	parse_lexer(t_list *list)
{
	t_list	*save = list;

	while (save)
	{
		if (save->type_id == 1)
		{
			if (save->next->type_id == 1)
			{
				printf("Error: Two consecutives pipe.\n");
				return ;
			}
		}
		if (save->type_id == 5)
		{
			if (save->next->type_id == 5)
			{
				printf("Error: Two consecutives && (Search the name yourself.).\n");
				return ;
			}
		}
		save = save->next;
	}
}

// void	parse_sup_tab(char **tab)
// {

// }

t_list *lexer(t_env *env, t_list *str)
{
    t_list *list = NULL;
    t_list *tmp = malloc(sizeof(t_list) * 100);
    char **tab = NULL;
	char *tp = (char *)str->content;
	int	val_test;
	val_test = checking_closed(tp);
	if (val_test == 0 || val_test == -1 || val_test == -2)
	{
		if (val_test == -2)
			return (list);
		// cmd_quote = dquote_mod(tp, val_test);
		printf("Error: Finishing quote is missing.\n");
		return (list);
	}
    int i = 0;
    tab = ft_ssplit(tp);
	afftab(tab);
    while (tab[i])
    {
		if (ft_strlen(tab[i]) == 0)
			return (list);
		if (tab[i][0] == '\n' && tab[i][1])
			return (list);
        list = ft_lstnew(tab[i]);
		printf("sorti\n");
		if (list->type_id == 6)
		{
			printf("Unexpected token.\n");
			return (NULL);
		}
		printf("tes la\n");
		if (list->type_id == 4)
			search_env_content(env, list);
		list->next = tmp;
        tmp = list;
        i++;
    }
    afflist(list, "Lexer");
	parse_lexer(list);
	return (list);
}


int main(int ac, char **av, char **env)
{
    t_env *list;
	t_list	*history = NULL;
    t_list *str = NULL;
	history = ft_lstnew(NULL);
    list = get_env(env);
    (void)ac;
    (void)av;
	int	i = 0;

	while (list[i].name)
	{
		printf("Env[i] -- >%s\n", list[i].content);
		i++;
	}
    while (42)
	{
		// printf("0\n");
	 	ft_putstr("minishell>");
        str = ft_lstnew(get_next_line(0));
		ft_lstadd(&history, str);
        lexer(list, str);
	}
    return (0);
}