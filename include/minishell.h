/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:37:50 by alpicard          #+#    #+#             */
/*   Updated: 2023/12/03 17:45:35 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Readline/history.h"
# include "../Readline/readline.h"
# include "../libft/include/libft.h"
# include <pthread.h>
# include <signal.h>
# include <stdint.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# define PROMPT "Minishell-0.9$ "
# define HEREDOC "heredoc > "
//Token types 0-10
# define EMPTY 0
# define CMD 1
# define ARGS 2
# define PIPE 3        // |
# define REDIR_IN 4    // >
# define REDIR_OUT 5   // <
# define REDIR_dbl 9   // >>
# define REDIR_dbl2 10 // <<
# define ABS 6
# define FILE_OUT 7

//Modes 11-12
# define INTERACTIVE 11
# define CHILD 12
//FDs 20+
# define STDIN 20
# define STDOUT 21
# define STDERR 22

typedef struct s_token
{
	int					token_no;
	int					type;
	char				**cmd;
	char				*next_sep;
	int					errno;
	int					errnum;
	pid_t				child_pid;
	pid_t pid; // test al
	int					p_fd[2];

	int input;             // STDIN or pipe
	int output;            // STDOUT or pipe
	int fd_in;             // REDIR
	int fd_out;            //  REDIR
	int fd_hd;            //  HEREDOC
	struct s_environ *env; // address of env
	struct s_mini *mini;   // address of mini
	struct s_token		*next;
}						t_token;

typedef struct s_mini
{
	char				*input;
	char				**cmds;
	int					no_sep;
	int					no_wrds;
	char				**env;
	char				*SHLVL;
	char				*PATH;
	int					env_len;
	// struct s_env	*env_l;
	struct s_environ	*env_test;
	int					errno;
	struct s_token		*tokens;
	int					pid;
}						t_mini;

typedef struct s_environ
{
	char				**temp;
	char *env_var; // gauche du =
	char *env_val; // droite du =
	int					num;
	struct s_environ	*next;
}						t_environ;

typedef struct s_export
{
	char				**temp;
	char				*env_var;
	char				*env_val;
	struct s_export		*next;
}						t_export;

int						g_errno;

/*Builtins*/
int						ft_echo(t_token *token);
int						ft_pwd(t_token *token);
int						ft_env(t_token *token);
void					set_env(t_mini *mini, char **env);
int						ft_cd(t_mini *mini, t_token *token);
int						update_env_part(t_mini *mini, char *part, char *_new);
char					*get_env_part(t_mini *mini, char *part);
int						ft_unset(t_token *token);
int						ft_export(t_mini *mini, char **var);
int						ft_export2(t_mini *mini, char **var);
int						ft_builtins(t_token *token);
int						is_builtin(t_token *token);

/*Parse*/
int						ft_parse(t_mini *mini);
int						parse_mini_cmds(t_mini *mini);
int						is_empty(char *input);
int						has_equal_sign(char **var);
int						tokeniser(t_mini *mini);
char					**env_l_to_dbl_arr(t_environ *env);
char					*check_part(char *part);
int						check_pipe(t_mini *mini, int cmd_no);
int						check_valid_quotes(char *input);
void					set_err_code(int code);
int						has_dollar_sign(char *input);
char					*dollar_sign(char *mini_cmd);
int						has_quotes(char *str);

/*Env*/
t_environ	*new_env(char **var);
t_environ	*new_env2(char *var);
int						ft_set_env(t_mini *mini, char **env);
t_environ				*new_env_list(char *content);
void					ft_envadd_back(t_environ **env, t_environ *neo);
t_environ				*ft_envlast(t_environ *env);
t_environ				*init_env_list(t_mini *mini, int env_item);
void					print_env(t_environ *environ);
t_environ				*init_item(char *to_split);
void	do_export(t_mini *mini, t_export *_export, char **var);
int	export_no_input(t_mini *mini);
int	check_export(char **var);
t_export	*init_export(t_mini *mini, char **var);

/*Mini_split*/
int						no_of_words(char *s, int trigger, int i, int no_wrds);
int						word_len(char *s, int start);
char					**mini_split(char *s);
char					**ft_split2(char const *s, char *c);

/*Execute*/
void					exec_and_stuff(t_token *token);
char	*get_path(t_token *token);
void	absolute_path(t_token *token);
int						exec(t_token *token);
void					wait_pids(t_token *token);
int					heredoc(t_token *token);
void					do_pipe3(t_token *token);
void					do_pipe2(t_token *token);
void					do_pipe(t_token *token);
void					redir(t_token *token);
void					redir2(t_token *token);
void					redir_append(t_token *token);
char	**build_heredoc_cmd2(t_token *token);

/*Utils*/
char	*get_prompt(char *prt);
int						ft_len(char *s);
int						is_sep(char *str);
int						no_of_quotes(int max, char *s);
int						no_of_squotes(int max, char *s);
char					*ft_str_to_upper(char *s);
int						is_quoted(char *str);
int is_quote(int c);

/*Display test*/
void					print_array(t_mini *mini);
void					prt_array(t_mini *mini);
void					display_split(char **s, char *str);
void					print_token(t_mini *mini);
void					print_env_l(t_mini *mini);

/*Signals*/
void					init_signals(int mode);
void					ft_handler(int sig);
void					handler(int sig, siginfo_t *info, void *s);

/*Errors*/
int syntax_error(void);
int						invalid_path(char *error);
int						command_not_found(char *error);
int						is_a_directory(char *error);
void					set_err_code(int code);
/*Free*/
void					*releaser(char **table);
void					free_tokens(t_token *tokens);
void					free_env(t_environ *env);
int					free_minishell(t_mini *mini);
void					reset_minishell(t_mini *mini);
t_mini					*get_data(void);
void					free_export(t_export *exp);

/*TO DO

testing ++
Valgrind
Norminette

*/
#endif