#include "../inc/cub3d.h"

static void	parse_gun_texture(t_main_data *main_data)
{
	main_data->tex[4].img = mlx_xpm_file_to_image(main_data->mlx,
			"textures/gun.xpm",
			&(main_data->tex[4].tex_width), &(main_data->tex[4].tex_height));
	if (main_data->tex[4].img == NULL)
		printf("Gun image not found");
	main_data->tex[4].buff = (int *)mlx_get_data_addr(main_data->tex[4].img,
			&(main_data->tex[4].bpp), &(main_data->tex[4].l_len),
			&(main_data->tex[4].endian));
}

bool valid_content(char **file_content, t_main_data *main_data)
{
    int index;
    int j;
    size_t i;
    i = 0;
    j = 0;

    if (!file_content || !main_data)
        return (false);
    if(!init_main_data(main_data)) 
        return(false);
    while(file_content && i < 6)
    {
        file_content[j] = skip_tab_spaces(file_content[j]);
        if(is_empty_line(file_content[j]))
        {
            j++;
            continue;
        }
        index = get_index(file_content[j]);
        if(index >= 0 && index <= 3)
        {
            printf("index : %d\n", index);
            if(!validate_textures(file_content[j], main_data))
                return(false);
            i++;
            printf("[validate_textures] texture validated successfully!\n");
        }
        else if(index == 4 || index == 5)
        {
            if(!validate_colors(file_content[j], main_data))
                return(false);
            i++;
        }
        else 
            return(false);
        if (i == 6)
            break;
        j++;
       
    }
    parse_gun_texture(main_data);
    if (!parse_map(file_content, ++j, main_data))
        return (false);
    i = 0;
    while (i < 4)
    {
        if (main_data->textures[i++].path == NULL)
        {
            printf("[validate_textures] Error: Missing texture at index %lu\n", i - 1);
            return (false);
        }
    } 
   
    return (true);
}

// printf("j before loop: %s", file_content[j]);
// printf("=== FLOOR COLOR ===\n");
// printf("Red:   %d\n", main_data->floor.red);
// printf("Green: %d\n", main_data->floor.green);
// printf("Blue:  %d\n", main_data->floor.blue);

// printf("=== CEILING COLOR ===\n");
// printf("Red:   %d\n", main_data->ceiling.red);
// printf("Green: %d\n", main_data->ceiling.green);
// printf("Blue:  %d\n", main_data->ceiling.blue);