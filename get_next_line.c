/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istripol <istripol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:10:28 by istripol          #+#    #+#             */
/*   Updated: 2024/03/26 06:20:30 by istripol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	cut_line(char **str)
{
	int		i;
	int		j;
	char	*ligne;

	i = 0;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	if ((*str)[i] == '\n')
	{
		ligne = malloc(sizeof(char) * i + 2);
		if (!ligne)
		{
			(*str) = NULL;
			return ;
		}
		i++;
	}
	else
		return ;
	j = -1;
	while (++j < i)
		ligne[j] = (*str)[j];
	ligne[j] = 0;
	free(*str);
	(*str) = ligne;
}

static void	get_buffer(char *ptr, char *ligne)
{
	int		i;
	char	*str;
	char	*nl;

	i = 0;
	nl = ft_strchr(ligne, '\n') + 1;
	if (nl)
		str = nl;
	else
		return ;
	while (str[i])
		*ptr++ = str[i++];
	*ptr = 0;
	return ;
}

static char	*get_final_line(char *ligne, char *buffer)
{
	if (ft_strchr(ligne, '\n'))
	{
		get_buffer(buffer, ligne);
		return (ligne);
	}
	return (ligne);
}

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE + 1];
	char			*ligne;
	int				red;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE < 1)
		return (NULL);
	red = 1;
	ligne = NULL;
	if (buffer[0] != 0)
		ft_strjoin(&ligne, buffer);
	while (red && !ft_strchr(buffer, '\n'))
	{
		red = read(fd, buffer, BUFFER_SIZE);
		if (red < 0)
			return (NULL);
		buffer[red] = 0;
		if (red == 0)
			break ;
		ft_strjoin(&ligne, buffer);
	}
	if (!get_final_line(ligne, buffer))
		return (NULL);
	return (ligne = get_final_line(ligne, buffer), cut_line(&ligne), ligne);
}
