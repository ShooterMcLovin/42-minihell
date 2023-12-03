/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdtests.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:16:15 by alpicard          #+#    #+#             */
/*   Updated: 2023/10/13 16:40:56 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int tata(void)
{
	// printf("%d\n%s", chdir(getenv("OLDPWD")), getenv("PWD"));
	
	return (chdir(getenv("OLDPWD")));
}


int main()
{
	printf("%d", tata());
	printf("%s\n", getenv("PWD"));
}	