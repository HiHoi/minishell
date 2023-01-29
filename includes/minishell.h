/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosunglim <hosunglim@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 20:35:48 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/29 19:22:57 by hosunglim        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ERROR 1
# define SUCCESS 0
# define FAIL -1
# define T_WORD 10
# define T_PIPE 11
# define T_REDI 12
# define T_NULL 13

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <termios.h>
# include <term.h>

typedef struct s_info
{
	struct s_cmd	*cmd;
	char			**en;
}	t_info;

typedef struct s_cmd
{
	int				type;
	int				len;
	int				exec_flag;
	int				parent_flag;
	int				parse_flag;
	int				fd[2];
	char			*str;
	struct s_cmd	*left;
	struct s_cmd	*right;
}	t_cmd;

size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *ptr, int value, size_t num);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_calloc(size_t nelem, size_t elsize);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strchr(const char *str, int c);
int		ft_isdigit(int c);
char	*ft_strtrim(char const *s1, char const *set);

t_info	*init_info(char **envp);
t_cmd	*init_cmd(void);
void	start_shell(t_info *info);
int		error(t_info *info, char *s);
int		hs_error_return(t_info *info, t_cmd *cmd, char *s);
void	free_cmd(t_cmd *cmd);

void	parsing_cmd(t_info *info, char *buf);
void	hs_cmd(t_cmd *cmd, char ***envp);

int		check_type(t_cmd *cmd, char *buf);
int		count_line(char **line);
void	hs_parse_pipe(t_cmd *cmd, char *buf, int i);
void	hs_parse_redi(int idx, t_cmd *cmd, char *buf, int flag);
void	hs_parse_redi_double(t_cmd *cmd);

void	hs_do_something(t_info *info);
void	hs_redirect(t_cmd *cmd);
void	hs_search_tree(t_cmd *cmd, char ***envp);

void	hs_pipeline(t_cmd *cmd, char ***envp, int parent_fd[2]);
char	*pipe_parsing_cmd(char **path, char *cmd);
char	**pipe_parsing_envp(char ***envp);

int		hs_check_builtin(t_cmd *cmd);
void	hs_exec_builtin(t_cmd *cmd, char ***envp);
void	ft_env(t_cmd *cmd, char ***envp);
void	ft_pwd(t_cmd *cmd);
void	ft_export(t_cmd *cmd, char ***envp);
void	ft_unset(t_cmd *cmd, char ***envp);
int		ft_echo(t_cmd *cmd, char ***envp);

#endif