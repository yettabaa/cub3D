/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:37:07 by nfoughal          #+#    #+#             */
/*   Updated: 2023/06/22 04:34:40 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# include <stdlib.h>
# include <unistd.h>

char	*ftt_strjoin(char *s1, char *s2);
size_t	ftt_strlen(char *s);
int		ftt_strchr(char *s, int c);
char	*ftt_strdup(char *s1);
char	*get_next_line(int fd);
char	*read_record(int fd, char *record);
char	*get_line(char *record);
char	*new_record(char *record);
#endif
