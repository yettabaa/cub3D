/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 23:49:05 by yettabaa          #+#    #+#             */
/*   Updated: 2022/11/03 22:36:01 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_n(int n)
{
	long	i;
	long	nb;

	i = 0;
	nb = n;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb *= -1;
		i++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

static int	pow_10(int n)
{
	int	i;
	int	r;

	i = 1;
	r = 1;
	if (n < 0)
		i++;
	while (i < nb_n(n))
	{
		r *= 10;
		i++;
	}
	return (r);
}

char	*ft_itoa(int n)
{
	long	i;
	long	pow;
	long	nb ;
	char	*str;

	nb = n;
	pow = pow_10(n);
	str = (char *)malloc(nb_n(n) + 1);
	if (!str)
		return (NULL);
	i = 0;
	if (nb < 0)
	{
		str[i++] = '-';
		nb *= -1;
	}
	while (i < nb_n(n))
	{
		str[i++] = (nb / pow) + 48;
		nb = nb - (nb / pow * pow);
		pow /= 10;
	}
	str[i] = '\0';
	return (str);
}
