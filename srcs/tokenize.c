/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:17:59 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/15 19:54:19 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	syntax_simple_cmd(t_token *t)
// {
// 	if (t->type == T_WORD)
// 	{
// 		if (t->type == T_WORD)
// 			return (SUCCESS);
// 	}
// 	else
// 		return (FAIL);
// 	return (0);
// }

// int	syntax_io_redirect(t_token *t)
// {
// 	if (t->type == T_REDI && t->type == T_WORD)
// 		return (SUCCESS);
// 	else
// 		return (FAIL);
// 	return (0);
// }

// int	syntax_redirect(t_token *t)
// {
// 	syntax_io_redirect(t);
// 	if (t->type == T_REDI)
// 		syntax_redirect(t);
// 	return (0);
// }

// int	syntax_cmd(t_token *t)
// {
// 	syntax_simple_cmd(t);
// 	if (t->type == T_REDI)
// 		syntax_redirect(t);
// 	return (0);
// }

// int	syntax_pipeline(t_token *t)
// {
// 	syntax_cmd(t);
// 	if (t->type == T_PIPE)
// 		syntax_pipeline(t);
// 	return (0);
// }
