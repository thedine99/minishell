/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:47:57 by ntan              #+#    #+#             */
/*   Updated: 2022/04/08 17:37:24 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_heredoc
{
	char		*delim;
	char		*temp;
	int			fd;
	char		*str;
	int			expand;
}				t_heredoc;

typedef struct s_hd_list
{
	t_heredoc			*content;
	struct s_hd_list	*next;	
}				t_hd_list;

// tab: 1 = in, 2 = out, 3 = append, 4 = heredoc
typedef struct s_fd_order
{
	int			in;
	int			out;
	int			hd;
	int			append;
	int			*tab;
	int			i;
}				t_fd_order;

typedef struct s_block
{
	int			input_type;
	char		**input;
	int			input_fd;
	int			cmd_type;
	char		**cmd;
	char		*cmd_path;
	int			output_type;
	char		**output;
	char		**outputs_append;
	int			output_fd;
	int			*pipe;
	int			pid;
	int			cmd_i;
	t_fd_order	*t_fd;
	t_heredoc	*heredoc;
}				t_block;

typedef struct s_list
{
	t_block			*content;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

int		ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
char	*ft_itoa(int n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstadd_back(t_list **alst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/** GARBAGE COLLECTOR **/

# define ERROR 0
# define NOERR 1

typedef struct s_memlst		t_memlst;

struct	s_memlst
{
	void		*address;
	t_memlst	*nxt;
};

int		mempush(void *ptr, const size_t byte, const size_t size);
int		memfree(void *ptr);
int		memrelease(void);

#endif