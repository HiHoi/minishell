/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:51:36 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/11 19:54:48 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	char	*path;
	char	dir[30];
	int		ch;

	path = "/";
	dir[30] = "Current Directory: ";
	ch = chdir(path);
	if (ch == 0)
		printf("Change!\n");
	else
		printf("Failed change directory!\n");
	write(1, dir, strlen(dir));
	if (system("pwd") == -1)
		perror("command failed\n");
	return (0);
}
