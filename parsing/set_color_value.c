#include "../inc/cub3d.h"

char *skip_digits(char *line)
{
    while (ft_isdigit(*line))
        line++;
    return line;
}

char *skip_comma(char *line)
{
    if (*line == ',')
        return line + 1;
    return NULL;
}

char *set_color_value(char *line, int *value, bool is_comma)
{
    if (!ft_isdigit(*line))
    {
        printf("[set_color_value] Error: Expected digit\n");
        return NULL;
    }
    *value = ft_atoi(line);
    if (*value < 0 || *value > 255)
    {
        printf("[set_color_value] Error: Value should be in [0,255]\n");
        return NULL;
    }
    line = skip_digits(line);
    line = skip_tab_spaces(line);
    
    if (is_comma)
    {
        if (*line != ',')
        {
            printf("[set_color_value] Error: Expected comma after value\n");
            return NULL;
        }
        line++; // пропускаем запятую
        return skip_tab_spaces(line);
    }
    else
    {               
        // Последнее значение: нельзя допускать запятую
        if (*line == ',')
        {
            printf("[set_color_value] Error: Unexpected comma after last value\n");
            return NULL;
        }
        return skip_tab_spaces(line);
    }
}
