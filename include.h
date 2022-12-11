#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "../lib/libft/libft.h"
# include "../lib/gnl/get_next_line.h"

typedef struct s_env
{
	char	*name;
	char	*content;
}
t_env;


typedef struct s_token
{
	enum
	{
		TK_TXT,
		TK_EQUALS,
		TK_REDI,
		TK_PIPE,
		TK_DOLAR,
		TK_QUOTE,
	} e_type;
	char *value;
} t_token;
// structure liste chainée classique

typedef struct s_list
{
	void			*content;
	int				type_id;
	struct s_list	*next;
}				t_list;

//------------------------------------utils.c------------------------------------
t_list	*ft_lstnew(void *content);
t_list *ft_lstadd(t_list **alst, t_list *new);
int ft_strlen(const char *s);
char *ft_strchr(const char *s, int c);
char *ft_strsub(char const *s, unsigned int start, size_t len);
void ft_putstr(char *str);
int	ft_strcmp(char *s1, char *s2);
char **ft_strsplit(char *str, char delim);
void afftab(char **tab);
void afflist(t_list *list, char *name);
int	closed_elem(char *str, char c);
int	checking_closed(char *tp);
void	ft_lstadd_back(t_list **lst, t_list *new);
char **ft_ssplit(char *str);

//------------------------------------- main.c -------------------------------------
t_env *get_env(char **env);
t_list *lexer(t_env *env, t_list *str);
int main(int ac, char **av, char **env);

#endif