/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:13:18 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/12 13:49:12 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <term.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termcap.h>

//컴파일시 -lncurses 옵션 필수

int	nbr_length(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	get_cursor_position(int *col, int *rows)
{
	int		a;
	int		i;
	int		ret;
	int		temp;
	char	buf[255];

	a = 0;
	i = 1;
	write(0, "\033[6n", 4);
	ret = read(0, buf, 254);
	buf[ret] = '\0';
	while (buf[i])
	{
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			if (a == 0)
				*rows = atoi(&buf[i]) - 1;
			else
			{
				temp = atoi(&buf[i]);
				*col = temp - 1;
			}
			a++;
			i += nbr_length(temp) - 1;
		}
		i++;
	}
}

int	putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

void	move_cursor_left(int *col, int *row, char *cm)
{
	if (*col == 0)
		return ;
	--(*col);
	tputs(tgoto(cm, *col, *row), 1, putchar_tc);
}

void	move_cursor_right(int *col, int *row, char *cm)
{
	++(*col);
	tputs(tgoto(cm, *col, *row), 1, putchar_tc);
}

void	delete_end(int *col, int *row, char *cm, char *ce)
{
	if (*col != 0)
		--(*col);
	tputs(tgoto(cm, *col, *row), 1, putchar_tc);
	tputs(ce, 1, putchar_tc);
}

int	main(void)
{
	struct termios	term;
	int				c;
	int				row;
	int				col;
	char			*cm;
	char			*ce;

	tcgetattr(0, &term);
	term.c_cflag &= ~ICANON;
	term.c_cflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	tgetent(NULL, "xterm");
	cm = tgetstr("cm", NULL);
	ce = tgetstr("ce", NULL);
	c = 0;
	while (read(0, &c, sizeof(c)) > 0)
	{
		get_cursor_position(&col, &row);
		if (c == 4479771)
			move_cursor_left(&col, &row, cm);
		else if (c == 4414235)
			move_cursor_right(&col, &row, cm);
		else if (c == 127)
			delete_end(&col, &row, cm, ce);
		else
		{
			col++;
			write(0, &c, 1);
		}
		c = 0;
	}
}
