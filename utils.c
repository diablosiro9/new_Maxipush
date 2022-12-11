#include "../include/include.h"

int ft_lstsize(t_list *lst)
{
	t_list *tmp;
	int i;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void afflist(t_list *list, char *name)
{
	printf("Lstsize de list == %d\n", ft_lstsize(list));
	printf("		--------------------\n\
		| \e[44m Affichage %s\e[0m |\n\
		---------------------\n",
		   name);
	// (void)name;
	while (list)
	{
		printf("%s , type_id == %d\n", (char *)list->content, list->type_id);
		list = list->next;
	}
	printf("\n");
}

void ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *tmp;

	if (!*lst)
	{
		*lst = new;
		return;
	}
	else
	{
		tmp = *lst;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_list *ft_lstadd(t_list **alst, t_list *new)
{
	t_list *tmp;

	tmp = *alst;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*alst = new;
	return (new);
}

int	parse_str(char *str)
{
	int	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '|' && str[i + 1] == str[i])
				return (0);
			if (str[i] == '&' && str[i + 1] == str[i])
				return (0);
			i++;
		}
	}
	return (1);
}
//NEW_SPLIT
char **ft_ssplit(char *str)
{
    int i = 0;
    int j = 0;
    char **tab = malloc(sizeof(char *) * ft_strlen(str));

    while (str[i])
    {
        if (str[i] == 34)
        {
            tab[j] = ft_strsub(str, 0, i);
            str = str + i + 1;
            i = 0;
            j++;
        }
        if (str[i] == 60)
        {
            tab[j] = ft_strsub(str, 0, i);
            str = str + i + 1;
            i = 0;
            j++;
        }
        else
            i++;
    }
    tab[j] = ft_strsub(str, 0, i);
    tab[j + 1] = NULL;
    return (tab);
}
//END FIN SPLIT

t_list *ft_lstnew(void *content)
{
	t_list *new;
	size_t i = 0;
	char *str = (char *)content;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	if (str != NULL)
	{
		if (str[i] == '|')
			new->type_id = 1;
		else if (str[i] == '>' || str[i] == '<')
		{
			if (str[i] == '<')
				new->type_id = 2;
			else
				new->type_id = 3;
		}	
		else if (str[i] == '$')
			new->type_id = 4;
		else if (str[i] == '&')
			new->type_id = 5;
		else
			new->type_id = 0;
	}
	else
		new->type_id = 0;
	if (parse_str((char *)content) == 0)
		new->type_id = 6;
	new->next = NULL;
	return (new);
}

char *ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (!*s++)
			return (NULL);
	}
	return ((char *)s);
}

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void ft_putstr(char *str)
{
	int i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

char *ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *str;
	size_t i;

	i = 0;
	if (!s)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char **ft_strsplit(char *str, char delim)
{
	char **tab;
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * (ft_strlen(str) + 1))))
		return (NULL);
	while (str[i])
	{
		if (str[i] == delim)
		{
			tab[j] = ft_strsub(str, k, i - k);
			k = i + 1;
			j++;
		}
		i++;
	}
	tab[j] = ft_strsub(str, k, i - k);
	tab[j + 1] = NULL;
	return (tab);
}

void afftab(char **tab)
{
	int i = 0;
	while (tab[i])
	{
		printf("tab[%d] = %s et la taille = %d\n", i, tab[i], ft_strlen(tab[i]));
		i++;
	}
}

int closed_elem(char *str, char c)
{
	int i = 0;
	// int	start = 0;
	// int	end = ft_strlen(str) - 1;
	int flag = 0;
	int counter = 0;
	char *start = ft_strchr(str, c);
	if (start == NULL)
		return (1);
	while (start[i])
	{
		if (counter == 1 && start[i] == c)
		{
			counter = 0;
			flag = 0;
		}
		if (flag == 1 && start[i] == c)
		{
			counter = 1;
			flag = 0;
		}
		if (start[i] == c && counter != 1)
			flag = 1;
		i++;
	}
	return (counter);
}

int	is_quote(char *tp, char c)
{
	int	i = 0;
	if (!tp)
		return 1;
	while (tp[i])
	{
		if (tp[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int checking_closed(char *tp)
{
	if (!tp)
		return (-2);
	int val_test = closed_elem(tp, '"');
	if (val_test == 0)
		return (0);
	val_test = closed_elem(tp, '\'');
	if (val_test == 0)
		return (-1);
	return (val_test);
}