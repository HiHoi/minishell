/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcgetset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:41:30 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/12 13:47:00 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int	main(void)
{
	struct termios	term;
	int				c;

	tcgetattr(0, &term);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	c = 0;
	while (read(0, &c, sizeof(c)) > 0)
	{
		printf("keycode : %d\n", c);
		c = 0;
	}
}
