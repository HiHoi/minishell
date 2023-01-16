/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opendir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:13:40 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/11 21:17:18 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

int	main(void)
{
	DIR				*dir_info;
	struct dirent	*dir_entry;

	dir_info = opendir(".");
	if (dir_info != NULL)
	{
		dir_entry = readdir(dir_info);
		while (dir_entry)
		{
			printf("%s\n", dir_entry->d_name);
			dir_entry = readdir(dir_info);
		}
		closedir(dir_info);
	}
}
