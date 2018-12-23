/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 20:35:11 by tduval            #+#    #+#             */
/*   Updated: 2018/12/23 22:32:19 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "libft.h"

static char		*get_name(char *str)
{
	char	*name;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!(name = ft_strnew(i)))
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

static char		*get_value(char *str)
{
	while (*str && *str != '=')
		str++;
	return (ft_strdup(str + 1));
}

t_env	*get_env(void)
{
	extern char	**environ;
	t_env		*new;
	t_env		*or;
	int			i;

	i = 0;
	new = 0;
	or = 0;
	while (environ[i])
	{
		if (!new)
		{
			if (!(new = (t_env *)malloc(sizeof(t_env))))
				return (0);
			if (!(new->var = get_name(environ[i])))
				return (0);
			if (!(new->val = get_value(environ[i])))
				return (0);
			or = new;
		}
		else
		{
			if (!(new->next = (t_env *)malloc(sizeof(t_env))))
				return (0);
			if (!(new->next->var = get_name(environ[i])))
				return (0);
			if (!(new->next->val = get_value(environ[i])))
				return (0);
			new = new->next;
		}
		i++;
	}
	new->next = 0;
	return (or);
}