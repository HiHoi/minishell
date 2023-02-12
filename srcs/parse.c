/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:23:51 by hoslim            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/01/16 20:27:29 by hoslim           ###   ########.fr       */
=======
/*   Updated: 2023/02/12 20:34:35 by hoslim           ###   ########.fr       */
>>>>>>> hoslim
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

<<<<<<< HEAD
int	check_type(t_cmd *cmd, char *buf)
=======
void	hs_lexical_pipe(t_cmd *cmd, char *buf)
>>>>>>> hoslim
{
	int		i;
	int		idx;

	i = -1;
	idx = 0;
	while (buf[++i])
	{
		if (buf[i] == '|')
		{
<<<<<<< HEAD
			cmd->type = T_PIPE;
			return (T_PIPE);
=======
			idx = i;
			break ;
>>>>>>> hoslim
		}
	}
	hs_parse_pipe(cmd, buf, idx);
}

int	hs_check_redi(char *buf, char redi)
{
	int	i;
	int	idx;

	i = -1;
	idx = -1;
	while (buf[++i])
	{
		if (buf[i] == redi)
		{
<<<<<<< HEAD
			cmd->type = T_REDI;
			return (T_REDI);
=======
			if (buf[i + 1] == redi)
				i++;
			return (i);
>>>>>>> hoslim
		}
	}
<<<<<<< HEAD
	return (T_WORD);
=======
	return (idx);
>>>>>>> hoslim
}

// cat a > "bb>>" = X

void	hs_lexical_redi(t_cmd *cmd, char *buf)
{
	int		i;
	int		j;
	char	**parse;

	cmd->left = init_cmd();
	cmd->left->parse_flag = 1;
	cmd->right = init_cmd();
	parse = hj_redc_spilit(buf);
	cmd->left->str = ft_strdup(parse[0]);
	cmd->right->str = ft_strdup(parse[1]);
	if (parse[0])
	{
		cmd->left->left = init_cmd();
		cmd->left->right = init_cmd();
	}
	i = hs_check_redi(cmd->left->str, '<');
	j = hs_check_redi(cmd->left->str, '>');
	if (i != -1)
		hs_parse_redi(i, cmd->left, cmd->left->str, 1);
	else
		hs_parse_redi(j, cmd->left, cmd->left->str, 2);
	hs_parse_redi_double(cmd->left);
	free_parse(parse);
}

<<<<<<< HEAD
void	hs_lexical_pipe(t_cmd *cmd, char *buf)
{
	int		i;
	char	*left_str;
	char	*right_str;

	i = -1;
	while (buf[++i])
	{
		if (buf[i] == '|')
			break ;
	}
	cmd->left = ft_calloc(1, sizeof(t_cmd));
	left_str = ft_substr(buf, 0, i);
	cmd->left->str = ft_strdup(left_str);
	cmd->right = ft_calloc(1, sizeof(t_cmd));
	right_str = ft_substr(buf, i + 1, ft_strlen(buf) - i);
	cmd->right->str = ft_strdup(right_str);
}

void	hs_lexical_redi(t_cmd *cmd, char *buf)
{
	int		i;
	char	*left_str;
	char	*right_str;

	i = -1;
	while (buf[++i])
	{
		if (buf[i] == '<')
		{
			if (buf[i + 1] == '<')
				i++;
			break ;
		}
		else if (buf[i] == '>')
		{
			if (buf[i + 1] == '>')
				i++;
			break ;
		}
	}
	cmd->left = ft_calloc(1, sizeof(t_cmd));
	left_str = ft_substr(buf, 0, i);
	cmd->left->str = ft_strdup(left_str);
	cmd->right = ft_calloc(1, sizeof(t_cmd));
	right_str = ft_substr(buf, i + 1, ft_strlen(buf) - i);
	cmd->right->str = ft_strdup(right_str);
}

=======
>>>>>>> hoslim
void	hs_check_lexical(t_cmd *cmd, char *buf)
{
	if (check_type(cmd, buf) == T_WORD)
		return ;
<<<<<<< HEAD
	else if (check_type(cmd, buf) == T_PIPE)
		hs_lexical_pipe(cmd, buf);
	else if (check_type(cmd, buf) == T_REDI)
		hs_lexical_redi(cmd, buf);
	if (cmd->left != NULL)
		hs_check_lexical(cmd->left, cmd->left->str);
	if (cmd->right != NULL)
		hs_check_lexical(cmd->right, cmd->right->str);
}

void	parsing_cmd(t_info *info, char *buf)
{
	check_type(info->cmd, buf);
	if (info->cmd->type != T_WORD)
		hs_check_lexical(info->cmd, buf);
	else
		info->cmd->str = ft_strdup(buf);
=======
	if (cmd->type == T_PIPE)
		hs_lexical_pipe(cmd, buf);
	else if (cmd->type == T_REDI)
		hs_lexical_redi(cmd, buf);
	if (cmd->left)
		check_type(cmd->left, cmd->left->str);
	if (cmd->right)
		check_type(cmd->right, cmd->right->str);
	if (cmd->left && cmd->type != T_REDI)
		hs_check_lexical(cmd->left, cmd->left->str);
	if (cmd->right && cmd->right->parse_flag == 0)
		hs_check_lexical(cmd->right, cmd->right->str);
}

//여기서 누수 생기는데 나중에 해결 요함

void	parsing_cmd(t_info *info, char *buf)
{
	info->cmd = init_cmd();
	info->cmd->str = ft_strdup(buf);
	check_type(info->cmd, info->cmd->str);
	if (info->cmd->type != T_WORD)
		hs_check_lexical(info->cmd, buf);
>>>>>>> hoslim
}
