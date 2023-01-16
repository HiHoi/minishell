/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcsetattr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:39:14 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/12 13:11:13 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>

struct termios org_term;
struct termios new_term;

void	save_input_mode(void)
{
	tcgetattr(0, &org_term);
}

void	set_input_mode(void)
{
	tcgetattr(0, &new_term);
	new_term.c_cflag &= ~(ICANON | ECHO);
	new_term.c_cc[VMIN] = 1;
	new_term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &new_term);
}

void	reset_input_mode(void)
{
	tcsetattr(0, TCSANOW, &org_term);
}

int	main(void)
{
	int	ch;
	int	idx;

	ch = 0;
	idx = -1;
	save_input_mode();
	set_input_mode();
	while (read(0, &ch, 1) > 0)
	{
		if (ch == 4)
		{
			if (idx == -1)
				exit(0);
			else
				continue ;
		}
		else if (ch == 127)
		{
			if (idx >= 0)
			{
				--idx;
				write(0, "\b \b", 3);
			}
		}
		else if (ch == '\n')
			break ;
		else
		{
			++idx;
			write(0, &ch, sizeof(int));
		}
		ch = 0;
	}
	reset_input_mode();
	return (0);
}
