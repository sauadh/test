#include "../inc/cub3d.h"

long long int convert_rgb (t_rgb *layer)
{
    return ( layer->red * (pow(256, 2)) + (layer->green * 256) + layer->blue);
}

bool validate_colors(char *file_content, t_main_data *main_data)
{
    t_rgb *layer;


    if (file_content[0] == 'F' && (file_content[1] == ' ' || file_content[1] == '\t'))
        layer = &main_data->floor;
    else if (file_content[0] == 'C' && (file_content[1] == ' ' || file_content[1] == '\t'))
        layer = &main_data->ceiling;
    else
    {
        printf("[validate_colors] Error: should start with 'F' or 'C'\n");
        return (false);
    }
    if(layer->is_set)
    {
        printf("[validate_colors] Error: duplicate colors\n");
        return (false);
    }

    file_content += 1; // пропускаем 'F' или 'C'
    file_content = skip_tab_spaces(file_content); // пропускаем пробелы перед числами

    file_content = set_color_value(file_content, &layer->red, true);
    if (!file_content) return (false);

    file_content = set_color_value(file_content, &layer->green, true);
    if (!file_content) return (false);

    file_content = set_color_value(file_content, &layer->blue, false);
    if (!file_content) return (false);
    // printf(" checking blue %d\n", layer->blue);
    file_content = skip_tab_spaces(file_content);
    if (*file_content != '\0' && *file_content != '\n')
    {
        printf("[validate_colors] Error: Extra characters after color\n");
        return (false);
    }
    layer->is_set = true;
    layer->in_int = convert_rgb(layer);
    printf("[validate_colors] color validated successfully!\n");
    return (true);
}

