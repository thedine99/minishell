/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:45:26 by ntan              #+#    #+#             */
/*   Updated: 2022/04/04 15:26:04 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	open_trioput_file(char **tab, int option)
{
	int	i;
	int	fd;

	fd = -2;
	i = 0;
	while (tab[i])
	{
		if (option == 1)
			fd = open(tab[i], O_RDWR);
		else if (option == 2)
			fd = open(tab[i], O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
		else if (option == 3)
			fd = open(tab[i], O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
		if (fd == -1)
		{
			ft_error(ft_error_file_opening(tab[i], option), tab[i], 1);
			return (-1);
		}
		if (tab[i + 1] != NULL)
			close(fd);
		i++;
	}
	return (fd);
}

int	open_heredoc_fd(t_block *block)
{
	generate_random_file(&block->heredoc->temp, &block->heredoc->fd);
	ft_putstr_fd(block->heredoc->str, block->heredoc->fd);
	close(block->heredoc->fd);
	block->heredoc->fd = open(block->heredoc->temp, O_RDWR);
	return (block->heredoc->fd);
}

int	open_fds(t_block *block)
{
	int	tmp;

	if (block->input_type == 1)
		block->input_fd = open_trioput_file(block->input, 1);
	else if (block->input_type == 2)
		block->input_fd = open_heredoc_fd(block);
	if (block->input_fd == -1)
		return (-1);
	tmp = -2;
	if (block->output_type == 1)
		block->output_fd = open_trioput_file(block->output, 2);
	else if (block->output_type == 2)
		block->output_fd = open_trioput_file(block->outputs_append, 3);
	if (block->output_type == 1)
		tmp = open_and_close(block->outputs_append, 3);
	else if (block->output_type == 2)
		tmp = open_and_close(block->output, 2);
	if (block->output_fd == -1 || tmp == -1)
		return (-1);
	return (0);
}

int	open_pipes(t_block *block)
{
	int	*fd;

	fd = NULL;
	mempush(&fd, sizeof(int), 2);
	block->pipe = fd;
	if (block->cmd_i != 0)
	{		
		if (pipe(fd) == -1)
			return (ft_error(TOO_MANY_FDS, "pipe error", 129), 1);
	}
	else
	{
		block->pipe[0] = -2;
		block->pipe[1] = -2;
	}
	return (0);
}