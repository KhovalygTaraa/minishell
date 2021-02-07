/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 15:49:30 by swquinc           #+#    #+#             */
/*   Updated: 2021/01/31 20:01:35 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFFER_SIZE 100
# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct		s_bilist
{
	void			*content;
	struct s_bilist	*next;
	struct s_bilist	*prev;
}					t_bilist;

t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
t_bilist			*ft_blstnew(void *content);
void				ft_blstadd_back(t_bilist **lst, t_bilist *new);
void				ft_blstadd_front(t_bilist **lst, t_bilist *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *a, int b, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *string);
size_t				ft_strlcpy(char *dst, const char *src, size_t s);
size_t				ft_strlcat(char *dst, const char *src, size_t s);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *s1, const char *s2, size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_atoi(const char *str);
float				ft_atof(const char *str);
double				ft_atod(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_calloc(size_t count, size_t size);
void				*ft_line_malloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_free(char *s1, const char *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				**ft_split_upd(char const *s, char *str);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(const char c, int fd);
void				ft_putstr_fd(const char *c, int fd);
void				ft_putendl_fd(const char *c, int fd);
void				ft_putnbr_fd(int n, int fd);
int					get_next_line(int fd, char **line);

#endif
