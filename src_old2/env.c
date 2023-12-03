#include "../include/miniHell.h"

int env_malloc(char **env)
{
	int env_size = 0;
	int x = 0;
	t_ev *head;
	if (!env || !env[0])
		return 0;
	t_minishell *mini;
	mini = get_minishell();
	while (env[env_size])
		env_size++;
	mini->ev = malloc(sizeof(t_ev*) * env_size + 1);
	mini->ev_len = env_size;
	if(!mini->ev)
		return 0;
	return 1;
}

int init_env(char **env)
{
	t_minishell *mini;
	t_ev *head;
	int x = 0;
	mini = get_minishell();
	head = mini->ev;
	while (env[x])
	{
		mini->ev = malloc (sizeof(t_ev));
		mini->ev->content = ft_strdup(env[x]);
		x++;
		mini->ev = mini->ev->next;
	}
	mini->ev = head;
	return 1;
}

int ev_to_dbl(void)
{
	t_minishell *mini;
	t_ev *head;
	mini = get_minishell();
	int x = 0;
	mini->ev_dbl = malloc(mini->ev_len + 1);
	if (!mini->ev_dbl)
		return 0;
	head = mini->ev;
	while (head)
	{
		mini->ev_dbl[x] = ft_strdup(head->content);
		x++;
		head = head->next;
	}
	mini->ev_dbl[x] = NULL;
	if (x != mini->ev_len)
		ft_printf("ev_to dbl FAIL\n");
	return 1;
}

int set_shlvl(void)
{
	return 1;
}

int set_oldpwd(void)
{
	return 1;
}

int set_env(char **env)
{
	t_minishell *mini;
	// int *results;
	// int no_fn = 4;
	// ft_memset (results,1,no_fn);
	int x = 0;
	int res = 0;
	mini = get_minishell();
	env_malloc(env);
	init_env(env);
	set_shlvl();
	set_oldpwd();
	// ev_to_dbl();
	/*while (res < no_fn)
	{
		if (results[res] != 1)
			return FAILURE;
		res++;
	}
	return SUCCESS;
	*/
	return 1;
}