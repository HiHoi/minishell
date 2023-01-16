/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 20:35:48 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/16 12:52:12 by hoslim           ###   ########.fr       */
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

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
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
	char			**envp;
}	t_info;

typedef struct s_cmd
{
	int				type;
	int				len;
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

t_info	*init_info(void);
void	start_shell(t_info *info);
int		error(t_info *info, char *s);

void	parsing_cmd(t_info *info, char *buf);

#endif