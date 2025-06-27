#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#define END '\0'

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_len(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_itoa(pid_t n)
{
	int		len;
	char	*num;

	len = ft_len(n);
	num = malloc(len + 1);
	if (!num)
		return (NULL);
	num[len] = '\0';
	if (n == 0)
		num[0] = '0';
	if (n < 0)
		num[0] = '-';
	if (n == -2147483648)
	{
		num[1] = '2';
		n = 147483648;
	}
	if (n < 0)
		n = -n;
	while (n)
	{
		num[--len] = n % 10 + '0';
		n /= 10;
	}
	return (num);
}

void	sigma(int signal)
{
	static unsigned char	current_char;
	static int				bit;

	current_char = current_char | (signal == SIGUSR1);
	bit++;
	if (bit == 8)
	{
		if (current_char == END)
			write(1, "\n", 1);
		else
			write(1, &current_char, 1);
		bit = 0;
		current_char = 0;
	}
	else
		current_char <<= 1;
}

int	main(void)
{
	char	*server_pid;

	server_pid = ft_itoa(getpid());
	write(1, server_pid, ft_strlen(server_pid));
	write(1, "\n", 1);
	free(server_pid);
	signal(SIGUSR1, sigma);
	signal(SIGUSR2, sigma);
	while (1)
		pause();
	return (0);
}
