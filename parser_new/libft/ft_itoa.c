/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:38:20 by ladrian           #+#    #+#             */
/*   Updated: 2021/10/13 21:10:06 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_razriad(int nbr)
{
	int	count;

	count = 0;
	while (nbr / 10)
	{
		nbr /= 10;
		count++;
	}
	return (count + 1);
}

static int	ft_abs(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	else
		return (nbr);
}

static void	ft_strrev(char *str)
{
	size_t	length;
	size_t	i;
	char	tmp;

	length = ft_strlen(str);
	i = 0;
	while (i < length / 2)
	{
		tmp = str[i];
		str[i] = str[length - i - 1];
		str[length - i - 1] = tmp;
		i++;
	}
	str[length] = '\0';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	size_t	length;

	sign = (n < 0);
	str = ft_calloc(ft_razriad(n) + sign + 1, sizeof(*str));
	if (!(str))
		return (NULL);
	if (n == 0)
		str[0] = '0';
	length = 0;
	while (n != 0)
	{
		str[length++] = '0' + ft_abs(n % 10);
		n = (n / 10);
	}
	if (sign)
		str[length] = '-';
	ft_strrev(str);
	return (str);
}
