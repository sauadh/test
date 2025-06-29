#include "../inc/cub3d.h"

void free_split(char **split)
{
    int i = 0;
    if (!split)
    return;
    while (split[i])
    free(split[i++]);
    // printf("splitted %i parts\n", i);
    free(split);
}

void exit_program(char *message, void *data)
{
    (void)data;
    if(message)
    printf("%s", message);
    exit(EXIT_FAILURE);
}

void  clean_2darray(char **content)
{
    int i;
    i = 0;
    while (content[i] != NULL)
    {
        free(content[i]);
        i++;
    }
    free(content);
}

void clean(char **content)
{
    if(!content)
    return;
    else
    clean_2darray(content);
    return;
}
bool is_empty_line(char *str)
{
    int i;
    int n_symb;
    
    i = 0;
    n_symb = 0;
    if(!str)
        return(true);
    while (str[i] != '\0')
    {
        if(str[i] != '\t' && str[i] != ' ' && str[i] != '\n')
        n_symb++;
        i++;
    }
    if(n_symb == 0)
        return(true);
    return(false);
    
}
void clean_main_data(t_main_data *main_data)
{
    int i;
    
    i = 0;
    while (i < 4)
    {
        if (main_data->textures[i].path)
            free(main_data->textures[i].path);
        if (main_data->tex[i].img != NULL)
			mlx_destroy_image(main_data->mlx, main_data->tex[i].img);

        i++;
    }
    if (main_data->maplines)
        clean(main_data->maplines);
}