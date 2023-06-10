/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelkama <moelkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:06:22 by moelkama          #+#    #+#             */
/*   Updated: 2023/06/01 14:10:05 by moelkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strncopy(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
}

void	check_herdoc(char **arr)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arr[i])
	{
		if (!ft_strcmp(arr[i], "<<"))
			count++;
		i++;
	}
	if (count > 16)
	{
		ft_putstr_fd("maximum here-document count exceeded", 2, 1);
		ft_free(arr);
		exit (2);
	}
}

int	check_qutes(char *limit)
{
	while (*limit)
	{
		if (*limit == '\'' || *limit == '"')
			return (1);
		limit++;
	}
	return (0);
}
