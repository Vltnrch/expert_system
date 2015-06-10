/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_engine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/04 17:21:40 by vroche            #+#    #+#             */
/*   Updated: 2015/06/10 17:34:35 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expertsystem.h"

/* Calcul de 'G op D' */
int	ft_do_op(int left, char op, int right)
{
	if (left == UNDETER || right == UNDETER)
	{
		if (op == '+' && (left == FALSE || right == FALSE))
			return (FALSE);
		else if (op == '|' && (left == TRUE || right == TRUE))
			return (TRUE);
		return (UNDETER);
	}
	else if (op == '+')
		return (left & right);
	else if (op == '|')
		return (left | right);
	else if (op == '^')
		return (left ^ right);
	return (UNDETER);
}

/* Donne le nombre identifiant la prioritÈ de l'opÈrateur donnÈ */
int	ft_priority_op(char op)
{
	if (op == '+')
		return (3);
	if (op == '|')
		return (2);
	if (op == '^')
		return (1);
	return (0);
}

/* Renvoie une valeur positive si 'op' est un opÈrateur gÈrÈ. */
int	ft_isop(char op)
{
	if (op == '+' || op == '|' || op == '^')
		return (1);
	return (0);
}

/*
 * '_dl' signifie : 'dÈj‡ lu' :
 *      G_dl : opÈrande qui a dÈj‡ ÈtÈ lue par une instance de la fonction et qui va servir
 *      d'opÈrande de gauche pour la nouvelle instance.
 *      Op_dl : idem, mais Áa concerne l'opÈrateur.
 * 'prio_op_pre' : prioritÈ de l'opÈrateur prÈcÈdent (pour que les calculs se fassent dans l'ordre) :
 *      L'instance de la fonction retourne lorsqu'elle a trouvÈ un opÈrateur qui a une prioritÈ plus
 *      faible que 'prio_op_pre', pour que la fonction appelante fasse le calcul.
*/
int	ft_calc_rule(t_env *env, const char *calcul, int *left_dl, char *op_dl, int prio_op_pre, const char **p_calcul)
{
	int		left;
	int		right; /* opèrande de gauche et opèrande de droite */
	char	op;
	char	op_next;
	int		reverse;

	/* *** initialisations *** */
	/* si left_dl est un pointeur valide */
	reverse = 0;
	if (left_dl != NULL)
		left = *left_dl;
	else
	{ /* sinon on lit left */
		if (*calcul == '!')
		{
			reverse = 1;
			calcul++;
		}
		if (*calcul == '(')
			left = ft_calc_rule(env, calcul+1, NULL, NULL, 0, &calcul);
		else
		{
			left = ft_engine(env, *calcul);
			calcul++;
		}
		if (reverse == 1)
		{
			if (left != UNDETER)
				left = !left;
			reverse = 0;
		}
	}
	/* si op_dl est un pointeur valide */
	if (op_dl != NULL)
		op = *op_dl;
	else
	{ /* sinon on lit l'opèrateur */
		op = *calcul;
		calcul++;
	}
	/* *** boucle des calculs *** */
	while (op != '\0' && op != ')' && ft_priority_op(op) > prio_op_pre)
	{
		/* lecture de l'opèrande de droite */
		if (*calcul == '!')
		{
			reverse = 1;
			calcul++;
		}
		if (*calcul == '(')
			right = ft_calc_rule(env, calcul+1, NULL, NULL, 0, &calcul);
		else
		{
			right = ft_engine(env, *calcul);
			calcul++;
		}
		if (reverse == 1)
		{
			if (right != UNDETER)
				right = !right;
			reverse = 0;
		}
		/* opèrateur next */
		op_next = *calcul;
		calcul++;
		if (ft_isop(op_next) && ft_priority_op(op_next) > ft_priority_op(op))
			right = ft_calc_rule(env, calcul, &right, &op_next, ft_priority_op(op), &calcul);
		left = ft_do_op(left, op, right);
		op = op_next;
	}
	/* *** fin de la boucle des calculs *** */
	/* mise ‡ jour de l'opèrateur next pour la fonction appelante */
	if (op_dl != NULL)
		*op_dl = op_next;
	/* a pour effet d'indiquer ‡ la fonction appelante jusqu'o˘
		la fonction appelèe a lu la chaine 'calcul' */
	if (p_calcul != NULL)
		*p_calcul = calcul;
	return (left);
}

int		ft_engine(t_env *env, char name)
{
	int		status;
	t_list	*lrules;
	t_rules *rule;
	char	*calc_rule;
	int		reverse;

	status = UNDETER;
	if (ft_fact_isinsearch(env, name))
		return (UNDETER);
	if ((status = ft_getstatus_fact(env, name)) != DETER)
		return (status);
	else
	{
		ft_changeinsearch_fact(env, name, 1);
		lrules = env->lrules;
		while (lrules)
		{
			reverse = 0;
			rule = lrules->content;
			if ((calc_rule = ft_strchr(rule->after, name)))
			{
				if (calc_rule != rule->after)
					if (*(calc_rule - 1) == '!')
						reverse = 1;
				calc_rule = rule->before;
				status = ft_calc_rule(env, calc_rule, NULL, NULL, 0, NULL);
				if (status != UNDETER)
				{
					if (reverse == 1)
						status = !status;
					ft_changestatus_fact(env, name, status);
					ft_changeinsearch_fact(env, name, 0);
					return(status);
				}
			}
			lrules = lrules->next;
		}
		ft_changeinsearch_fact(env, name, 0);
	}
	return (status);
}

void	ft_backward_chaining(t_env *env)
{
	int		result;
	char	*questions;
	int		reverse;

	result = TRUE;
	questions = env->questions;
	while (*questions)
	{
		reverse = 0;
		if (*questions == '!')
		{
			reverse = 1;
			questions++;
		}
		result = ft_engine(env, *questions);
		if (reverse == 1 && result != UNDETER)
			result = !result;
		printf("Resultat de %c : %d\n", *questions, result);
		questions++;
	}
}