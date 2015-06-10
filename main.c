/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 15:13:03 by hleber            #+#    #+#             */
/*   Updated: 2015/06/10 18:35:36 by hleber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expertsystem.h"

void		ft_cut_rules(t_env *env, t_expsys *exsy)
{
	int		len;
	char	*tmp;
	char	*before;
	char	*after;

	len = 0;
	tmp = exsy->str;
	while (*tmp && *tmp++ != '=')
		len++;
	before = (char *)malloc((len + 1) * sizeof(char));
	before = ft_strncpy(before, exsy->str, len);
	exsy->str += len + 2;
	tmp = exsy->str;
	while (*tmp++)
		len++;
	after = (char *)malloc((len + 1) * sizeof(char));
	after = ft_strncpy(after, exsy->str, len);
	ft_add_rules(env, before, after);
}

void		ft_createlist_facts(t_env *env)
{
	t_rules		*rules;
	t_list		*lrules;
	char		*tmp;

	lrules = env->lrules;
	while (lrules != NULL)
	{
		rules = lrules->content;
		tmp = rules->before;
		while (*tmp)
		{
			if (*tmp >= 'A' && *tmp <= 'Z')
				ft_add_facts(env, *tmp, UNDETER);
			tmp++;
		}
		tmp = rules->after;
		while (*tmp)
		{
			if (*tmp >= 'A' && *tmp <= 'Z')
			{
				ft_add_facts(env, *tmp, DETER);
				if (ft_fact_isexist(env, *tmp))
					ft_changestatus_fact(env, *tmp, DETER);
			}
			tmp++;
		}
		lrules = lrules->next;
	}
}

float		add_ascii(char *s1)
{
	int len;
	int len2;
	
	len = 0;
	len2 = 1;
	while (*s1)
	{
		if ((*s1 >= 'A' && *s1 <= 'Z') || *s1 == '^' || *s1 == '|' || *s1 == '+')
		{
			len += (int)*s1;
			len2 += len * (int)*s1;
		}
		s1++;
	}
	return (len / (float)len2);
}

int		ft_check_char(char *s1, char *s2)
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

int			check_same_char(t_env *env)
{
	t_rules     *rule;
    t_list      *lrules;
	char		*tmp;
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
		while (*tmp)
		{
            if (*tmp >= 'A' && *tmp <= 'Z')
				if (ft_strchr(tmp + 1, *tmp) != NULL)
					return (0);
            tmp++;
        }
		lrules = lrules->next;
	}
	return (1);
}

int			ft_check_no_multi_rules(t_env *env)
{
	t_rules		*rule;
	t_rules		*rule2;
	t_list      *lrules;
	t_list		*lrules2;
	float		len;

	lrules = env->lrules;
	while (lrules)
	{
		rule = lrules->content;
		len = add_ascii(rule->before);
		lrules2 = env->lrules;
		while (lrules2)
		{
			rule2 = lrules2->content;
			if (len == add_ascii(rule2->before))
			{
				if ((rule != rule2) && ((add_ascii(rule->after) == add_ascii(rule2->after)) ||
				ft_check_char(rule->after, rule2->after) == 0))
				{
					printf("%s, %s\n", rule->after, rule2->after);
					return (0);
				}
			}
			lrules2 = lrules2->next;
		}
		lrules = lrules->next;
	}
	lrules = env->lrules;
	while (lrules)
    {
        rule = lrules->content;
        len = add_ascii(rule->after);
        lrules2 = env->lrules;
        while (lrules2)
        {
            rule2 = lrules2->content;
            if (len == add_ascii(rule2->after))
            {
                if ((rule != rule2) && ((add_ascii(rule->before) == add_ascii(rule2->before)) ||
										ft_check_char(rule->before, rule2->before) == 0))
                {
                    printf("%s, %s\n", rule->before, rule2->before);
                    return (0);
                }
            }
            lrules2 = lrules2->next;
        }
        lrules = lrules->next;
    }
	return (1);
}

void		ft_init_facts(t_env *env)
{
	char	*tmp;

	tmp = env->initfacts;
	while (*tmp)
	{
		if (*tmp >= 'A' && *tmp <= 'Z')
		{
			if (ft_fact_isexist(env, *tmp))
				ft_changestatus_fact(env, *tmp, TRUE);
			else
				ft_add_facts(env, *tmp, TRUE);
		}
		tmp++;
	}
}

void		ft_perror_exit(const char *str)
{
	ft_putstr_fd(str, 2);
	ft_putendl_fd(" Error", 2);
	exit(EXIT_FAILURE);
}

void		parse_arg(t_env *env, int ac, char **av)
{
	t_expsys	exsy;
	int			fd;
	char		*buf;

	t_facts		*fact;
	t_list		*lfacts;

	env->lrules = NULL;
	env->lfacts = NULL;
	exsy.str = NULL;
	env->initfacts = NULL;
	env->questions = NULL;
	if (ac != 2)
	{
		ft_putstr("usage : ./expert-system test/file.txt\n");
		exit (0);
	}
	if ((fd = open(av[1], O_RDONLY)) == -1)
		ft_perror_exit("Open File:");
	while (get_next_line(fd, &buf) > 0)
	{
		exsy.str = buf;
		del_isspace(&exsy);
		if (valid_file(&exsy) == 0)
			ft_perror_exit("File:");
		if (valid_rules(&exsy) == 0)
			ft_perror_exit("Rules:");
		if (check_par(&exsy) != 0)
			ft_perror_exit("Rules Bracket:");
		if (*(exsy.str) != 0)
		{
			if (*(exsy.str) != '=' && *(exsy.str) != '?')
				ft_cut_rules(env, &exsy);
			else if (*(exsy.str) == '=')
			{
				if (env->initfacts != NULL)
					ft_perror_exit("Multiple initial facts lines:");
				env->initfacts = ft_strdup(exsy.str + 1);
			}
			else if (*(exsy.str) == '?')
			{
				if (env->questions != NULL)
					ft_perror_exit("Multiple questions lines:");
				env->questions = ft_strdup(exsy.str + 1);
			}
		}
		free(buf);
	}
	if (env->initfacts == NULL)
		ft_perror_exit("Where is initial facts ?! (=[...]):");
	if (env->questions == NULL || *(env->questions) == 0)
		ft_perror_exit("Where is the question ?! (?...):");
	if (env->lrules == NULL)
		ft_perror_exit("Where is the rules ?!:");
	if ((ft_check_no_multi_rules(env) == 0) || (check_same_char(env) == 0))
		ft_perror_exit("Rules:");
	ft_createlist_facts(env);
	ft_init_facts(env);
	lfacts = env->lfacts;
	while (lfacts != NULL)
	{
		fact = lfacts->content;
		printf("Name : %c || Status : %d\n", fact->name, fact->status);
		lfacts = lfacts->next;
	}
	printf("Question : %s\n", env->questions);
	if (close(fd) == -1)
		ft_perror_exit("expert-system");
	if (!exsy.str)
		ft_putstr("expert-system: Empty file\n");
}

int				main(int ac, char **av)
{
	t_env	env;

	parse_arg(&env, ac, av);
	ft_backward_chaining(&env);
	return (0);
}
