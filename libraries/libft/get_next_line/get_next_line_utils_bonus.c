/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:15:02 by mprazere          #+#    #+#             */
/*   Updated: 2025/06/03 15:04:33 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	size_t	space;
	char	*str;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	if (ft_strlen_gnl(s1) > (size_t)-1 - ft_strlen_gnl(s2) - 1)
		return (NULL);
	space = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	str = malloc(sizeof(char) * (space + 1));
	space = 0;
	if (!str)
		return (NULL);
	while (s1[space])
		str[i++] = s1[space++];
	space = 0;
	while (s2[space])
		str[i++] = s2[space++];
	str[i] = '\0';
	return (str);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	unsigned char	chr;

	if (!s)
		return (NULL);
	chr = c;
	while (*s)
	{
		if (*s == chr)
			return ((char *)s);
		s++;
	}
	if (chr == '\0')
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen_gnl(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup_gnl(const char *s)
{
	size_t	i;
	size_t	a;
	char	*dpl;

	a = 0;
	i = ft_strlen_gnl(s);
	dpl = malloc(sizeof(char) * (i + 1));
	if (!dpl)
		return (NULL);
	while (a < i)
	{
		dpl[a] = s[a];
		a++;
	}
	dpl[a] = '\0';
	return (dpl);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen_gnl(s);
	if (start >= s_len)
		return (ft_strdup_gnl(""));
	if (len > s_len - start)
		len = s_len - start;
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
