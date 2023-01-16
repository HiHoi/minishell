/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:55:53 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/11 21:11:48 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int	main(void)
{
	int			ret;
	int			l_ret;
	struct stat	buf;

	ret = stat("/usr", &buf);
	l_ret = lstat("/usr", &buf);
	if (ret < 0 || l_ret < 0)
	{
		printf("Error\n");
		return (0);
	}
	printf("RET[%d] SIZE[%lld]\n", ret, buf.st_size);
	printf("L_RET[%d] SIZE[%lld]\n", l_ret, buf.st_size);
	return (0);
}
