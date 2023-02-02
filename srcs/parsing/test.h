/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 20:03:24 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/02 20:13:21 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include <stdlib.h>
# include <stdio.h>

int		hj_set_count(char *str);
int		*hj_set_seting(char *str, int count);
char	*hj_str_save(char *str, int i, int j);
int		hj_mal_size(char *str, char set);
int		hj_compare_push(char *str, int i, char set);

int		hj_sp_mal_size(char *str);
int		hj_pashing_push(char *str, int *i, char set);
int		hj_check_small(char *str);
char	*hj_del_small(char *str);

int		hj_sp_mal_size(char *str);
int		hj_set_compare_push(char *str, int i);
int		hj_compare_push2(char *str, int *i);
int		hj_set_mal_size(char *str);

char	**hj_save_split(char *str, int size);
char	*hj_compare_split(char *str, int *idx, int *setpoint);
int		*hj_setpoint_seting(char *str);
int		*hj_point_set(char *str, int *set, int setcount, int encount);
int		hj_encount(char *str);

char	*hj_split_str_join(char **split);
char	*hj_ft_strjoin(char *str, char *str2);
char	*hj_ft_strdup(char *str);
void	all_free(char **str);

void	ft_error(void);
int		hj_isseting(int i, int *set, int count);
char	*hj_split_join(char *str, char **envp);
char	**hj_split_cmd(char *str, char **envp);
int		hj_ft_strlen(char *str);

char	**hj_change_split(char **str, char **envp);
char	*hj_envp_change(char *str, char **envp);
char	*hj_find_envp_val(char *str, int *i, char **envp);
char	*hj_envp_name(char *str);
char	*hj_envp_plus_str(char *set, char *str, int i);

char	*hj_envp_val(char *envp);
int		hj_is_envp(char *str, char *envp);
int		hj_ft_isalpha(char c);
int		ft_isen(char c);

int		*hj_set_small_point(char *str);
int		hj_small_count(char *str);
char	*hj_del_small_save(char *str, int *set);

#endif
