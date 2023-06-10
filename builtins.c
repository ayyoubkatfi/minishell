/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatfi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:09:07 by akatfi            #+#    #+#             */
/*   Updated: 2023/06/10 15:31:41 by akatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_env(char **env, t_list **ptr, int show)
{
	int			i;
	static int	j;
	t_list		*head;

	i = -1;
	j = 0;
	if (!(*ptr) && j == 0)
	{
		while (env[++i])
			get_var_key(env[i], ptr, 1);
		j++;
	}
	head = (*ptr);
	if (!check_if_exit(head, "OLDPWD"))
		get_var_key("OLDPWD=", ptr, 1);
	while (head && show == 1)
	{
		if (head->key && head->var && head->key[0])
			printf("%s=%s\n", head->var, head->key);
		head = head->next;
	}
}

void	ft_unset(char **unset, t_list **ptr, int show)
{
	int		i;
	int		j;

	i = 0;
	while (unset[++i])
	{
		if (ft_check_unset(unset[i]))
		{
			if (show == 1)
			{
				j = 1;
				ft_printf("unset: `%s': not a valid identifier\n", unset[i]);
			}
		}
		else
			ft_remove2(ptr, unset[i]);
	}
	if (unset[i] == NULL && j == 1)
		exit(1);
}

void	ft_changepwd(char *path, t_list *pwd, t_list *head)
{
	int		i;
	int		j;
	char	**tab_dir;

	i = -1;
	j = 1;
	tab_dir = ft_split(path, '/');
	if (pwd->key)
		head->key = ft_alloc(pwd->key);
	while (ft_strcmp(".", path) && tab_dir[++i] && pwd)
	{
		if (ft_strcmp("..", tab_dir[i]) == 0)
			pwd->key = ft_delete_dirname(pwd->key);
		else
		{
			head = pwd;
			path = ft_link("/", tab_dir[i]);
			pwd->key = ft_link(pwd->key, path);
			free(path);
		}
	}
	ft_free_env(tab_dir);
}

void	ft_changeoldpwd(t_list	*head, char *path, t_list **ptr)
{
	t_list	*pwd;

	while (head)
	{
		if (ft_strcmp(head->var, "PWD") == 0)
			pwd = head;
		else if (ft_strcmp(head->var, "OLDPWD") == 0 && pwd)
		{
			if (head->key)
				free(head->key);
			break ;
		}
		head = head->next;
	}
	if (ft_check_pwd(path, *ptr) != 0)
	{
		head->key = pwd->key;
		pwd->key = ft_alloc(path);
	}
	else if (ft_check_pwd(path, *ptr) == 0)
		ft_changepwd(path, pwd, head);
}

void	ft_cd(char *path, t_list **ptr, int show)
{
	t_list	*head;

	head = *ptr;
	if (!path)
		path = ft_cd_home(*ptr, "HOME");
	if (chdir(path) == -1)
	{
		printerr(show, path);
		return ;
	}
	if (!(*ptr))
		return ;
	ft_changeoldpwd(head, path, ptr);
}
