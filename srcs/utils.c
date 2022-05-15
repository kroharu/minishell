#include "minishell.h"

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

int	ft_strcmp(char *str1, char *str2, char ch)
{
	size_t	i;

	if (!str1 && str2)
		return (*str2);
	else if (!str2 && str1)
		return (*str1);
	else if (str1 && str2)
	{
		i = 0;
		while ((str1[i] || str2[i]) && str1[i] != ch && str2[i] != ch)
		{
			if (str1[i] != str2[i])
				return (str1[i] - str2[i]);
			i++;
		}
	}
	return (0);
}

char	*ft_strnstr(char *haystack, char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack && haystack[i] && i < len)
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (needle[j] && haystack[i + j] == needle[j] && (i + j) < len)
				j++;
			if (!needle[j])
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2, int	free_mode)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	if (free_mode)
		free(s1);
	return (str);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*copy;

	if (!s1)
		return (0);
	i = 0;
	copy = malloc(sizeof(char) *(ft_strlen(s1) + 1));
	if (!copy)
		return (NULL);
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
