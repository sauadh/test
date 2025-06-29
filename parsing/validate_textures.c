#include "../inc/cub3d.h"
// static int have_all_textures(t_main_data *main_data)
// {
//     int i;
//     int n_text;

//     i = 0;
//     n_text = 0;
//     while (i < 4)
//     {
//         if (main_data->textures[i].path != NULL)
//             n_text++;
//         i++;
//     }
//     return (n_text);
// }

// static bool is_valid_path(const char *path)
// {
//     int i = 0;
//     // int fd;
//     size_t len;

//     if (!path)
//     {
//         printf("[is_valid_texture_path] Error: path is NULL\n");
//         return (false);
//     }

//     // Проверка: путь не пустой
//     while (path[i])
//     {
//         if (path[i] != ' ' && path[i] != '\t' && path[i] != '\n')
//             break;
//         i++;
//     }
//     if (path[i] == '\0')
//     {
//         printf("[is_valid_texture_path] Error: path is empty or only spaces\n");
//         return (false);
//     }

//     // Проверка: заканчивается на .xpm
//     len = ft_strlen(path);
//     if (len < 4)
//     {
//         printf("[is_valid_texture_path] Error: path is too short\n");
//         return (false);
//     }
//     printf("path=%s$\n", path);
//     // printf("taha: (%c)", path[len]);
//     // if (path[len] == '\n')
//     // {
//     //     printf("taha: (%s)", path + len - 4);
//     //     if (ft_strncmp(path + len - 4, ".xpm", 4) != 0)
//     //     {
//     //         // printf("file: %s\n",path + len - 4);
//     //         printf("[is_valid_texture_path] Error: path with nl does not end with .xpm: %s$\n", path);
//     //         return (false);
//     //     }
//     //     printf("[is_valid_texture_path] Path validated successfully: %s\n", path);
//     //     return (true);
//     // }
//     // printf("file: (%s)\n",path + len - 5);
//     if (ft_strncmp(path + len - 5, ".xpm", 4) != 0)
//     {
//         // printf("1");
//         // printf("file: (%s)\n",path + len - 4);
//         printf("[is_valid_texture_path] Error: path does not end with .xpm: %s$\n", path);
//         return (false);
//     }

//     // Проверка: файл существует
//     // fd = open(path, O_RDONLY);
//     // if (fd < 0)
//     // {
//     //     printf("[is_valid_texture_path] Error: file cannot be opened: %s\n", path);
//     //     return (false);
//     // }
//     // close(fd);

//     printf("[is_valid_texture_path] Path validated successfully: %s\n", path);
//     return (true);
// }

static bool is_valid_path(const char *path)
{
    int i = 0;
    // int fd;
    size_t len;

    if (!path)
        return (false);

    // Проверка: путь не пустой
    while (path[i])
    {
        if (path[i] != ' ' && path[i] != '\t' && path[i] != '\n')
            break;
        i++;
    }
    if (path[i] == '\0')
        return (false);
    char *temp;
    temp = ft_strtrim(path, " \n");
    printf("temp aysha checking %s5\n", temp);
    // Проверка: заканчивается на .xpm
    len = ft_strlen(temp);
    printf("checking len : %zu\n", len);
    if (len < 4)
        return (false);
    if (ft_strncmp(temp + len - 4, ".xpm", 4) != 0)
    {
        printf("check len: %zu\n", len);
        free(temp);
        return (false);
    }
    free(temp);
    return (true);
}

static bool set_path(char **splitted, t_main_data *main_data)
{
    int index;
    index = get_index(splitted[0]);
    printf("index = %i\n", index);
    if(index == -1 || main_data->textures[index].path != NULL)
    {
        printf("[set_path] Error: Invalid texture type or duplicate texture\n");
        return (false);
    }

    printf("[set_path] Checking path validity: %s\n", splitted[1]);
    if (!is_valid_path(splitted[1]))
    {
        printf("[set_path] Error: Invalid texture path: %s\n", splitted[1]);
        return (false);
    }
    printf("[set_path] Saving path: %s into texture index %d\n", splitted[1], index);
    main_data->textures[index].path = ft_strdup(splitted[1]);
    if (!main_data->textures[index].path)
    {
        // free(main_data->textures[index].path);
        printf("[set_path] Error: ft_strdup failed\n");
        return (false);
    }
    main_data->tex[index].img = mlx_xpm_file_to_image(main_data->mlx, main_data->textures[index].path,
			&(main_data->tex[index].tex_width), &(main_data->tex[index].tex_height));
	if (main_data->tex[index].img == NULL)
		printf( "Incorrect file path used for one or more");
	main_data->tex[index].buff = (int *)mlx_get_data_addr(
			main_data->tex[index].img,
			&(main_data->tex[index].bpp),
			&(main_data->tex[index].l_len),
			&(main_data->tex[index].endian));
    return (true);
}

bool validate_textures(char *file_content, t_main_data *main_data)
{
    int i;
    i = 0;
    char **splitted;
        printf("[validate_textures] Checking line: %s\n", file_content);
            if(get_index(file_content) != -1)
            {
                splitted = ft_split(file_content, ' ');
                // printf("split : %s\n\n\n\n", splitted[1]);
                if (!splitted || !splitted[0] || !splitted[1] || !is_empty_line(splitted[2]))
                {
                    // printf("have splitted[2]=%s$\n", splitted[2]);
                    printf("[validate_textures] Error: invalid split in line: %s\n", file_content);
                    return (free_split(splitted), false);
                }
                printf("[validate_textures] Splitted parts: %s | %s\n", splitted[0], splitted[1]);
                if (!set_path(splitted, main_data))
                {
                    printf("[validate_textures] Error: failed to set path for line: %s\n", file_content);
                    
                    return (free_split(splitted), false);
                }
                free_split(splitted);
            }
            else
            {
                printf("[validate_textures] Error: wrong texture type: %s\n", file_content);
                return (false);
            }
            // i++;

        i = 0;
        if (i == 4)
            printf("[validate_textures] All textures validated successfully!\n");
        return(true);
}

