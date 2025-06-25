#include "../inc/cub3d.h"
static bool invalid_char(t_main_data *main_data)
{
	int	i;
	int	j;

	i = 0;
	while (i < main_data->map_height)
	{
		j = 0;
		while (main_data->maplines[i][j])
		{
			if (!ft_strchr("NEWS01 ", main_data->maplines[i][j]))
            {
                printf("invalid characters in the map\n");
                    return (false);
            }
			j++;
		}
		i++;
	}
	return(true);
}

static bool store_map(char **map_lines, int j, t_main_data *main_data)
{
    int index;
    index = 0;
    if(!main_data->map_height || main_data->map_height < 3)
        return(false);
    main_data->maplines = malloc((sizeof(char *)) * (main_data->map_height + 1));
    if(!main_data->maplines)
        return(false);
    while(index < main_data->map_height)
    {
        //main_data->maplines[index] = malloc(sizeof(char) * (main_data->map_width + 2));
        main_data->maplines[index] = malloc(main_data->map_width + 10); // generous safety margin
        if (!main_data->maplines[index])
            return (false);
        ft_bzero(main_data->maplines[index], main_data->map_width + 10); // zero memory to avoid uninitialized bytes
        // if(!main_data->maplines[index])
        //     return(false);
        // ft_strlcpy(main_data->maplines[index], map_lines[j], main_data->map_width + 1);
        ft_strlcpy(main_data->maplines[index], map_lines[j], main_data->map_width + 10);

        // while((int)ft_strlen(main_data->maplines[index]) < main_data->map_width) //while((int)ft_strlen(main_data->maplines[index]) < main_data->map_width) 
        // {
        //     // dprintf(2, "current line:   %d and len is:  %d\n", index, (int)ft_strlen(main_data->maplines[index]));
        //     ft_strlcat(main_data->maplines[index], " ", main_data->map_width + 1);
        // }
        int len = ft_strlen(main_data->maplines[index]);
        while (len < main_data->map_width)
        {
            main_data->maplines[index][len++] = ' ';
        }
        main_data->maplines[index][len] = '\0'; // ensure null-termination

        index++;
        j++;
    }
    main_data->maplines[index] = NULL;
    index = 0;
    // while (index < main_data->map_height)
    // {
    //     printf(" map: $%s$\n", main_data->maplines[index]);
    //     index++;
    // }
    return(true);
}

 static bool get_map_size(char **map_lines, int j, t_main_data *main_data)
{
    size_t height;
    size_t max_width;

    height = 0;
    max_width = 0;

    while(map_lines[j])
    {
        // printf("hello from get_map_size loop, j here = $%s$\n", map_lines[j]);
        if(!map_lines[j] || is_empty_line(map_lines[j]))
        {
            printf("empty line in the map\n");
            return(false);
        }
        height++;
        if(ft_strlen(map_lines[j]) > max_width)
            max_width = ft_strlen(map_lines[j]);
        j++;   
    }
    main_data->map_height = height;
    main_data->map_width = max_width;
    if(main_data->map_height < 3)
        {
            printf("map is too small\n");
            return (false);
        }
    printf("\n\nmap_height: %d\n", main_data->map_height);
    printf("map_width: %d\n", main_data->map_width);
    printf("j last: %s\n", map_lines[j]);
    
    return (true);
}

bool parse_map(char **map_lines, int j, t_main_data *main_data)
{
    (void)main_data;

    printf("initial j:  %d\n\n\n", j);
    printf("j после того как попала в функцию validate_map: %s\n", map_lines[j]);
    while(is_empty_line(map_lines[j]))
        j++;
    printf("j после loop пропуска пустых строк: %s\n", map_lines[j]);
    
    printf("post j:  %d\n", j);
    if(!get_map_size(map_lines, j, main_data))
        return(false);
    if(!store_map(map_lines, j, main_data))
        return(false);
    if(!invalid_char(main_data))
        return(false);
    // while(main_data->maplines)
    // {
        
    // }

    if(!validate_map(main_data))
        return(false);
    return (true);
}