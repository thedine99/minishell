/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:56:11 by cdine             #+#    #+#             */
/*   Updated: 2022/04/08 16:49:35 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	if_single_dollar_sign(t_index *i, char *res, char *line, t_prog *msh)
{
	char	*tmp;
	int		k;

	tmp = get_var_content(&line[i->i], msh);
	if (tmp == NULL)
	{
		(i->i)++;
		while (line[i->i] && ft_isalnum(line[i->i]) == 1)
			(i->i)++;
	}
	else
	{
		k = 0;
		while (tmp[k])
			res[(i->j)++] = tmp[k++];
		(i->i)++;
		while (line[i->i] && (ft_isalnum(line[i->i]) == 1 || line[i->i] == '_'))
			(i->i)++;
	}
}

void	if_dollar_sign(t_index *i, char *res, char *line, int open_d_quote)
{
	char	*tmp;
	int		k;

	if (line[i->i + 1] == '?')
	{
		k = 0;
		tmp = ft_itoa(i->msh->prev_err_code);
		while (k < ft_nblen(i->msh->prev_err_code))
			res[(i->j)++] = tmp[k++];
		i->i += 2;
	}
	else if (line[i->i + 1] == ' ' || line[i->i + 1] == '\0'
		|| line[i->i + 1] == '+' || line[i->i + 1] == '='
		|| (open_d_quote % 2 == 1 && line[i->i + 1] == '"'))
		res[(i->j)++] = line[(i->i)++];
	else if (line[i->i + 1] == '\'' || line[i->i + 1] == '"')
		(i->i)++;
	else if (ft_isalpha(line[i->i + 1]) == 0 && line[i->i + 1] != '_')
		i->i += 2;
	else
		if_single_dollar_sign(i, res, line, i->msh);
}

int	if_squote(t_index *i, int *open_d_quote, char *res, char *line)
{
	res[i->j++] = line[i->i++];
	if (*open_d_quote % 2 == 1)
		return (0);
	while (line[i->i] && line[i->i] != '\'')
		res[i->j++] = line[i->i++];
	res[i->j++] = line[i->i++];
	return (0);
}

void	alias_expansion(char *line, char *res, t_prog *msh, int heredoc)
{
	t_index	i;
	int		open_d_quote;

	open_d_quote = 0;
	i.i = 0;
	i.j = 0;
	i.msh = msh;
	while (line[i.i])
	{
		if (line[i.i] == '"')
		{
			open_d_quote++;
			res[i.j++] = line[i.i++];
		}
		else if (line[i.i] == '\'' && heredoc == 0)
			if_squote(&i, &open_d_quote, res, line);
		else if (line[i.i] == '$')
			if_dollar_sign(&i, res, line, open_d_quote);
		else if (line[i.i])
			res[i.j++] = line[i.i++];
		if (i.i > 0 && !line[i.i - 1])
			break ;
	}
	res[i.j] = '\0';
}
