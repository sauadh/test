#include "../inc/cub3d.h"

// char	*skip_empty_lines(int fd)
// {
// 	char	*line;

// 	line = get_next_line(fd);
// 	if (line)
// 	{
// 		while (is_empty_line(line) == true)
// 		{
// 			if (line)
// 				free(line);
// 			line = get_next_line(fd);
// 		}
// 		if (line)
// 			return (line);
// 	}
// 	return (NULL);
// }

char *skip_tab_spaces(char *line)
{
    while (*line == ' ' || *line == '\t')
        line++;
    return (line);
}

int get_index(const char *str)
{
    if (!ft_strncmp(str, "NO", 2))
    {
        printf("[get_index] Found NO\n");
        return NO;
    }
    if (!ft_strncmp(str, "SO", 2))
    {
        printf("[get_index] Found SO\n");
        return SO;
    }
     if (!ft_strncmp(str, "WE", 2))
    {
        printf("[get_index] Found WE\n");
        return WE;
    }
     if (!ft_strncmp(str, "EA", 2))
    {
        printf("[get_index] Found EA\n");
        return EA;
    }
    if (!ft_strncmp(str, "F", 1))
    {
        printf("[get_index] Found F\n");
        return F;
    }
    if (!ft_strncmp(str, "C", 1))
    {
        printf("[get_index] Found C\n");
        return C;
    }

    printf("[get_index] No matching texture or layer type found\n");
    return (-1);
}

bool valid_file(char *input)
{
    int fd;

    fd = open(input, O_RDONLY);
    if(fd < 3)
    {
        close(fd);
        return(false);
    }
    close(fd);
    return(true);
}

bool check_file_format(char *input)
{
    size_t len;
    len = ft_strlen(input);

    if(len >= 4 
        && (input[len - 1] == 'b' 
        && input[len - 2] == 'u' 
        && input[len - 3] == 'c'
        && input[len - 4] == '.'))
        return(true);
    return(false);
}

