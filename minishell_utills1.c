/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utills1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatfi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 11:37:55 by akatfi            #+#    #+#             */
/*   Updated: 2023/06/09 21:27:29 by akatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_pwd(void)
{
	char	pwd[OPEN_MAX];

	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
}

void	ft_printf(char *str, char *s)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '%' && str[i + 1] == 's')
		{
			j = 0;
			write(2, s, ft_strlen(s));
			i += 2;
		}
		else
		{
			write(2, &str[i], 1);
			i++;
		}
	}
}

void	ft_exit2(int i, char **ext)
{
	if (i > 2)
	{
		write(2, "exit\nexit: too many arguments\n", 30);
		*g_status = 256;
		return ;
	}
	write(1, "exit\n", 5);
	exit(ft_atoi(ext[1]));
}

void	ft_exit(char **ext)
{
	int	i;

	if (!ext[1])
	{
		write(1, "exit\n", 5);
		exit(WEXITSTATUS(*g_status));
	}
	i = -1;
	while (ext[1][++i])
	{
		if (!(ext[1][i] >= '0' && ext[1][i] <= '9') && ext[1][i] != ' ')
		{
			ft_printf("exit\nexit: %s: numeric argument required\n", ext[1]);
			exit(255);
		}
	}
	i = 1;
	while (ext[i])
		i++;
	ft_exit2(i, ext);
}

char	*to_lowor(char *s1)
{
	int		i;
	char	*str;

	if (!s1)
		return (NULL);
	i = 0;
	str = malloc(ft_strlen(s1) + 1);
	while (s1[i])
	{
		if (s1[i] >= 'A' && s1[i] <= 'Z')
			str[i] = s1[i] + 32;
		else
			str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
