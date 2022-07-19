#include "minishell.h"

char	*check_spe_char_bis(char *cmd, int i)
{
	if (cmd[i + 1] && cmd[i] != cmd[i + 1])
	{
		if (cmd[i] == '|' && check_str(cmd, 0, i) == 1)
			return (NULL);
		else if (cmd[i + 1] != ' ')
			return (add_space(cmd, i));
		else if ((cmd[i + 1] == ' ')
			&& (check_str(cmd, (i + 1), ft_strlen(cmd)) == 0))
			i++;
	}
	else if (cmd [i] == '<' && cmd[i + 1] == '<'
		&& (check_str(cmd, (i + 2), ft_strlen(cmd)) == 0))
		return (add_space_hereapp(cmd, i));
	else if (cmd[i] == '>' && cmd[i + 1] == '>'
		&& (check_str(cmd, (i + 2), ft_strlen(cmd)) == 0))
		return (add_space_hereapp(cmd, i));
	return (NULL);
}

char	*check_spe_char(char *cmd)
{
	int	i;
	int	len_tmp;

	i = -1;
	len_tmp = ft_strlen(cmd);
	while (cmd[++i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
			i += (ft_split_quotes(cmd, i) + 1);
		if (cmd[i] && check_char(cmd[i]) == 0)
			return (NULL);
		if (cmd[i] == '|' || cmd[i] == '>' || cmd[i] == '<')
		{
			cmd = check_spe_char_bis(cmd, i);
			if (cmd == NULL)
				return (NULL);
			if (cmd[i + 1] && cmd[i + 1] == ' ')
				i++;
		}
		if (ft_strlen(cmd) - len_tmp != 0)
		{
			i += ft_strlen(cmd) - len_tmp;
			len_tmp = ft_strlen(cmd);
		}
	}
	return (cmd);
}

