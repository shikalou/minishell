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
		else if (cmd[i] == '\"' && check_d == 0)
			check_d++;
		else if (cmd[i] == '\"' && check_d > 0)
			check_d--;
		i++;
	}
	return(check_d + check_s);
}

int	ft_check_pipe(char **cmd_split)
{
	int	i;

	i = -1;
	while (cmd_split[++i])
	{
		if (cmd_split[i][0] == '|')
		{
			if (i == 0)
				return (0);
			if (cmd_split[i + 1] && cmd_split[i + 1][0] == '|')
				return (0);
			else if (!cmd_split[i + 1])
				return (0);
		}
	}
	return (1);
}

char	*ft_add_space_pipe(char *cmd)
{
	int		i;
	int		j;
	int		pipe;
	char	*new;

	i = -1;
	pipe = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '|')
			pipe++;
	}
	new = malloc(sizeof(char) * ft_strlen(cmd) + pipe * 2 + 1);
	i = -1;
	j = 0;
	while (cmd[++i])
	{
		if (cmd[i] != '|')
		{
			new[j] = cmd[i];
		}
		if (cmd[i] == '|')
		{
			new[j] = ' ';
			new[j + 1] = cmd[i];
			new[j + 2] = ' ';
			j+=2;
		}
		j++;
	}
	free(cmd);
	printf("%s\n", new);
	return (new);
}

int	ft_parsing(char *cmd)
{
	char **cmd_split;

	if (ft_checkquotes(cmd) != 0)
	{
		write(2, "Error syntax\n", 13);
		return (0);
	}
	cmd = ft_add_space_pipe(cmd);
	cmd_split = ft_split(cmd, ' ');
	if (!ft_check_pipe(cmd_split))
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
		if (!cmd)
			return ;
		add_history(cmd);
		if(!ft_parsing(cmd))
			continue ;
	}
}

int	main()
{
	shellmini();
	printf("\nslt les gars\n");
	return (0);
}
