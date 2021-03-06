/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:08:08 by cdine             #+#    #+#             */
/*   Updated: 2022/04/07 18:49:23 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_invalid_identifier_export(char *str)
{
	int	i;

	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (1);
	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	ft_unset_from_tab(char **tab, int i)
{
	while (tab[i + 1])
	{
		tab[i] = tab[i + 1];
		i++;
	}
	tab[i] = NULL;
}

void	remove_from_tab(char **tab, char *var)
{
	int	i;
	int	size_var_name;

	var = ft_strjoin(var, "=");
	size_var_name = 0;
	while (var[size_var_name])
		size_var_name++;
	i = 0;
	while (tab[i])
	{
		if (ft_strncmp(var, tab[i], size_var_name) == 0)
		{
			ft_unset_from_tab(tab, i);
			break ;
		}
		i++;
	}
}

int	ft_unset(char **cmd, t_prog *msh)
{
	int	i;
	int	ret;

	ret = 0;
	i = 1;
	while (cmd[i])
	{
		if (ft_invalid_identifier_export(cmd[i]) == 1)
		{
			ft_error(INVALID_IDENTIFIER, ft_strjoin("export: `", cmd[i]), 1);
			ret = 1;
			i++;
			continue ;
		}
		remove_from_tab(msh->envp, cmd[i]);
		remove_from_tab(msh->export, cmd[i]);
		i++;
	}
	return (ret);
}
