/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:55:30 by kcisse            #+#    #+#             */
/*   Updated: 2024/12/13 15:46:30 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "./utils/utils.h"

int	ft_check_espace(char *av, int ac)
{
	int	i;

	if (av[0] == ' ' || av[ft_strlen(av) - 1] == ' ')
		return (0);
	i = 0;
	while (*av)
	{
		if (*av == ' ' && ac > 2)
			return (0);
		else if (*av == ' ')
			i++;
		else
			i = 0;
		if (i > 1)
			return (0);
		av++;
	}
	return (1);
}

int	ft_check_sign(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if ((av[i] == '+' || av[i] == '-') && !av[i + 1])
			return (0);
		if ((av[i] == '+' || av[i] == '-') && av[i + 1])
		{
			if (!ft_strchr("0123456789", av[i + 1]))
				return (0);
		}
		if ((av[i] == '+' || av[i] == '-') && av[i - 1])
		{
			if (ft_strchr("0123456789", av[i - 1]))
				return (0);
		}
		i++;
	}
	return (1);
}

int	ft_check_val(char *av, int ac)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (!ft_strchr("+-0123456789", av[i]) && ac > 2)
			return (0);
		i++;
	}
	return (1);
}

int	check_num(char *str, int index)
{
	int	i;

	i = 0;
	if (index == 1 && ft_atoi(str) > 200)
		error_printer("number of philosophers shoulld be <= 200.");
	while (str[i])
	{
		if (ft_atoi(str) <= 0)
			error_printer("number should be greater than 0.");
		if (ft_atoi(str) > INT_MAX)
			error_printer("number should be between 1 and 2147483647.");
		i++;
	}
	return (0);
}

int	check_args(int ac, char **av)
{
	int	i;

	if (ac != 6 && ac != 5)
		error_printer("should take exactly 5 or 6 arguments.");
	i = 1;
	while (av[i])
	{
		if (!ft_check_espace(av[i], ac))
			error_printer("check for spaces in arguments.");
		if (!ft_check_val(av[i], ac))
			error_printer("arg should only contain '+0123456789'");
		if (!ft_check_sign(av[i]))
			error_printer("check for signs in arguments.");
		check_num(av[i], i);
		i++;
	}
	return (1);
}
