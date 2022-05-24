#include "minishell.h"

int	ft_checkquotes(char *cmd)
{
	int	i;
	int	check_s;
	int	check_d;

	i = 0;
	check_s = 0;
	check_d = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' && check_s == 0)
			check_s++;
		else if (cmd[i] == '\'' && check_s > 0)
			check_s--;
		else if (cmd[i] == '\"'&& check_d ==0)
			check_d++;
		else if (cmd[i] == '\"' && check_d > 0)
			check_d--;
		i++;
	}
	return(check_d + check_s);
}

int	ft_parsing(char *cmd)
{
	if (ft_checkquotes(cmd) != 0)
	{
		write(2, "Error syntax\n", 13);
		return (0);
	}
	return (1);
}

void	shellmini(void)
{
	char *cmd;
	
	while (1)
	{
		cmd = readline("nelson et zor minishell$ ");
		add_history(cmd);
		printf("%s\n", cmd);
		if(!ft_parsing(cmd))
			continue ;
	}

}

int	main()
{
	shellmini();
	return (0);
}
