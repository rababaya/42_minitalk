/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:05:00 by rababaya          #+#    #+#             */
/*   Updated: 2025/03/23 13:05:27 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

void	error_handler(char *error_text);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *str, int fd);
void	ft_putnbr_fd(int n, int fd);

#endif
