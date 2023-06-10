/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utills2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatfi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:37:07 by akatfi            #+#    #+#             */
/*   Updated: 2023/06/10 15:23:50 by akatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(char **ptr)
{
	int	i;

	i = -1;
	if (!ptr[0])
		return ;
	while (ptr[++i])
		free(ptr[i]);
	free(ptr);
}

int	ft_lstsize_pipe(t_pipe *pipe)
{
	int	i;

	i = 0;
	if (!pipe)
		return (0);
	while (pipe)
	{
		i++;
		pipe = pipe->next;
	}
	return (i);
}

int	ft_check_pwd(char *pwd, t_list *ptr)
{
	char	*path;

	if (ft_strcmp("/", pwd) == 0 || pwd[0] == '/')
		return (4);
	path = ft_cd_home(ptr, "HOME");
	if (ft_strcmp(path, pwd) == 0)
		return (1);
	path = ft_cd_home(ptr, "PWD");
	if (ft_strcmp(path, pwd) == 0)
		return (2);
	path = ft_cd_home(ptr, "OLDPWD");
	if (ft_strcmp(path, pwd) == 0)
		return (3);
	return (0);
}

void	printerr(int show, char *path)
{
	if (show == 1)
	{
		if (path)
			ft_printf("cd : %s : no such file or directory\n", path);
		else
			write(2, "cd: HOME not set\n", 17);
		exit(1);
	}
}

void	ft_remove(t_list **ptr)
{
	t_list	*rm;

	rm = (*ptr);
	*ptr = (*ptr)->next;
	free(rm->key);
	free(rm->var);
	free(rm);
}
