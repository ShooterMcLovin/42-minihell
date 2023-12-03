#include "../include/miniHell.h"

t_minishell *get_minishell(void)
{
	static t_minishell *minishell;
	if (!minishell)
		minishell = malloc (sizeof(t_minishell *));
	return minishell;
}

void print_ev(void)
{
	t_minishell *mini;
	t_ev *head;
	mini = get_minishell();
	head = mini->ev;
	while (head->next->content)
	{
		ft_printf("%s\n", head->content);
		head = head->next;
	}
}

int main(int ac, char **av, char **env)
{
	t_minishell *minishell;
	minishell = get_minishell();
	int result;
	set_env(env);
	print_ev();
	/*
	parse
	token
	*/
	return result;
}