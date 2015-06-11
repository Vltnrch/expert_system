/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/11 14:08:05 by vroche            #+#    #+#             */
/*   Updated: 2015/06/11 14:20:42 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expertsystem.h"

float		add_ascii(char *s1)
{
	int len;
	int len2;

	len = 0;
	len2 = 1;
	while (*s1)
	{
		if ((*s1 >= 'A' && *s1 <= 'Z') \
			|| *s1 == '^' || *s1 == '|' || *s1 == '+')
		{
			len += (int)*s1;
			len2 += len * (int)*s1;
		}
		s1++;
	}
	return (len / (float)len2);
}

int			ft_check_char(char *s1, char *s2)
{
	while (*s1)
	{
		if (*s1 >= 'A' && *s1 <= 'Z')
			if (ft_strchr(s2, *s1) != NULL)
				return (0);
		s1++;
	}
	return (1);
}

static int	check_same_char_part(char *tmp)
{
	while (*tmp)
	{
		if (*tmp >= 'A' && *tmp <= 'Z')
		{
			if (ft_strchr(tmp + 1, *tmp) != NULL)
				return (0);
		}
		tmp++;
	}
	return (1);
}

int			check_same_char(t_env *env)
{
	t_rules	*rule;
	t_list	*lrules;
	char	*tmp;

	lrules = env->lrules;
	while (lrules)
	{
		rule = lrules->content;
		tmp = rule->before;
		while (*tmp)
		{
			if (*tmp >= 'A' && *tmp <= 'Z')
				if (ft_strchr(tmp + 1, *tmp) != NULL)
					return (0);
			tmp++;
		}
		tmp = rule->after;
		if (check_same_char_part(tmp) == 0)
			return (0);
		lrules = lrules->next;
	}
	return (1);
}
