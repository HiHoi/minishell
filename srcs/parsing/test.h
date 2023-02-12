/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:55:22 by hojsong           #+#    #+#             */
/*   Updated: 2023/02/12 20:22:05 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

int		hj_set_count(char *str);
int		*hj_set_seting(char *str, int count);
char	*hj_str_save(char *str, int i, int j);
int		hj_mal_size(char *str, char set);
int		hj_compare_push(char *str, int i, char set);
int		hj_sp_mal_size(char *str);
int		hj_pashing_push(char *str, int *i, char set);
int		*hj_check_small(char *str);
void	hj_is_set(char *str, int *idx, int *setpoint);
char	**hj_set_int(char *str, int *i);
int		hj_set_compare_push(char *str, int i, int *result, int *ri);
int		hj_sp_mal_size(char *str);
int		hj_set_compare_push(char *str, int i, int *result, int *ri);
int		hj_set_compare_push2(char *str, int i, int *result, int *ri);
int		hj_compare_push2(char *str, int *i);
int		hj_set_mal_size(char *str);
char	**hj_save_split(char *str, int size);
char	*hj_compare_split(char *str, int *idx, int *setpoint);
int		hj_point_checker(char *str, int *set, int *num, char com);
int		*hj_setpoint_seting(char *str);
int		*hj_point_set(char *str, int *set, int setcount, int encount);
int		hj_encount(char *str);
char	*hj_split_str_join(char **split, int size);
char	*hj_ft_strjoin(char *str, char *str2);
char	*hj_ft_strdup(char *str);
void	all_free(char **str, int size);
void	hj_ft_error(void);
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
int		hj_ft_isen(char c);
char	*hj_ft_atoi(int num);
int		hj_set_atoi_size(int num);
char	*hj_last_rt_string(char *str, char *str2);
char	**hj_del_small(char **str, int size);

#endif
