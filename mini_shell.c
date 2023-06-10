/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatfi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:10:16 by moelkama          #+#    #+#             */
/*   Updated: 2023/06/10 16:02:50 by akatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipes(t_pipe **pipes)
{
	t_pipe	*ptr;
	t_pipe	*swp;

	ptr = *pipes;
	swp = NULL;
	while (ptr)
	{
		if (ptr->cmd)
		{
			ft_free(ptr->cmd->cmd);
			free(ptr->cmd->path);
			free(ptr->cmd);
		}
		free(swp);
		swp = ptr;
		ptr = ptr->next;
	}
	free(swp);
}

void	check_line(char *line)
{
	if (!line)
	{
		write(1, "exit\n", 5);
		exit (WEXITSTATUS(*g_status));
	}
	if (*line)
		add_history(line);
}

int	main(int c, char **v, char **env)
{
	t_pipe	*pipe;
	char	*line;
	t_list	*envp;
	char	**my_env;

	(void)c;
	(void)v;
	ft_get_env(env, &envp, 0);
	signal(SIGINT, handel_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		g_status[2] = 0;
		my_env = ft_change_type(envp);
		line = readline("minishell> ");
		check_line(line);
		pipe = get_pipes(line, my_env);
		if (pipe && !ft_strcmp("exit", pipe->cmd->cmd[0]))
			ft_exit(pipe->cmd->cmd);
		else if (pipe)
			ft_multiple_cmd(pipe, my_env, &envp);
		free_pipes(&pipe);
		free(line);
		ft_free_env(my_env);
	}
}
