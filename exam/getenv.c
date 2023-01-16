/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:30:26 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/12 12:38:32 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	printf("Computer Name : %s\n", getenv("COMPUTERNAME"));
	printf("CPU count : %s\n", getenv("NUMBER_OF_PROCESSORS"));
	printf("Hostname : %s\n", getenv("HOSTNAME"));
	printf("Home : %s\n", getenv("HOME"));
	return (0);
}
