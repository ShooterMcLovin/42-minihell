/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:20:19 by siroulea          #+#    #+#             */
/*   Updated: 2023/10/09 13:59:07 by siroulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	char	**ar;
	int		filein;
	int		fileout;
	int		nb_child;
	int		**fd;
	pid_t	*child_pid;

}			t_data;

int			ft_strlen(char *str);
char		*ft_strtrim(char *s1, char *set);
char		*ft_strnstr(char *haystack, char *needle, size_t len);
char		*ft_strjoin(char *s1, char *s2);
void		*ft_free(char *str);
void		*ft_calloc(size_t count, size_t size);
void		ft_free_double_array(char **str);
char		**ft_split(char *s, char c);
char		*ft_substr(char *s, unsigned int start, size_t len);
void		error(void);
void		close_fd(void);
void		free_all(void);
void		pipe_fd(void);
void		open_filein(int argc, char **argv);
void		loop_fork(int argc, char **argv, char **env);
t_data		*get_data(void);
void		ft_free_fd(void);
int			open_file(char *argv, int i);
void		child(int i, int j, int argc, char **env);
void		do_cmd(char *argv, char **env);
char		*found_path(char *argv, char **env);

#endif

//fork
//acces
//excve
//https://www.codequoi.com/pourquoi-je-necris
// -plus-darticles-sur-les-projets-de-42/
