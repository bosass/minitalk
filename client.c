#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#define END '\0'

pid_t	ft_atoi(char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * sign);
}

void	send_signal(pid_t pid, char chr)
{
	int		i;
	char	temp;

	i = 7;
	temp = chr;
	while (i >= 0)
	{
		temp = chr >> i;
		if (temp % 2 == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		i--;
		usleep(205);
	}
}

int	main(int ac, char **av)
{
	pid_t	server_pid;
	int		i;
	char	*message;

	if (ac != 3)
	{
		write(1, "use server pid and message as parameters\n", 41);
		exit (0);
	}
	server_pid = ft_atoi(av[1]);
	i = 0;
	message = av[2];
	while (message[i] != '\0')
	{
		send_signal(server_pid, message[i]);
		i++;
	}
	send_signal(server_pid, END);
	return (0);
}
