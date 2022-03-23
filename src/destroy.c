/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:35:12 by ntan              #+#    #+#             */
/*   Updated: 2022/03/23 15:26:18 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_all_pipes(t_list *beg_all_pipes)
{
	t_list	*temp;

	temp = beg_all_pipes;
	while (temp)
	{
		close(temp->content->pipe[0]);
		close(temp->content->pipe[1]);
		temp = temp->next;
	}
}

void	close_trioput_fd(t_list *cmd)
{
	if (cmd->content->input_fd != -2)
		close(cmd->content->input_fd);
	if (cmd->content->output_fd != -2)
		close(cmd->content->output_fd);
}

void	set_err_status(int code, char *str)
{
	printf("%s\n", str);
	error_code = code;
}

void	*ft_error(int code)
{
	if (code == CMD_NOT_FOUND)
		set_err_status(127, "minishell: command not found (RTFM)");
	else if (code == FILE_NOT_FOUND)
		set_err_status(1, "minishell: no such file or directory");
	else if (code == QUOTE_NOT_CLOSED)
		set_err_status(1, "minishell: quote not closed");
	else if (code == PARSE_ERROR)
		set_err_status(0, "minishell: parse error");
	else if (code == PERMISSION_DENIED)
		set_err_status(0, "minishell: permission denied");
	return (NULL);
}