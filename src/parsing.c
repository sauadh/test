#include "../inc/cub3d.h"

static bool lines_counter(char *input, int *nbr_lines, int *empty_lines)
{
    int fd;
    fd = open(input, O_RDONLY);
    char *line;
    
    *empty_lines = 0;
    *nbr_lines = 0;
    while((line = get_next_line(fd)) != NULL)
    {
        (*nbr_lines)++;
        if(is_empty_line(line))
        (*empty_lines)++;
        free(line);
        line = NULL;
    }
    close(fd);
    if(*nbr_lines - *empty_lines < 7)
    {
        // printf("less then 7 lines\n");
        return(false);
    }
    return(true);

}
bool parse_content(char *input, char ***file_content)
{
    int nbr_lines;
    int fd;
    char *line;
    int empty_lines;
    int i;
    
    i = 0;
    line = NULL;
    // printf(">>> [parse_content] Start\n");
    if((lines_counter(input, &nbr_lines, &empty_lines)) == false)
    {
        // printf(">>> [parse_content] lines_counter failed\n");
        return (false);
    }
    // printf(">>> [parse_content] lines counted: %d (empty: %d)\n", nbr_lines, empty_lines);
    fd = open(input, O_RDONLY);
    if(fd < 0)
    {
        // printf(">>> [parse_content] cannot open file again\n");
        return (false);
    }
    *file_content = malloc(sizeof(char *) * (nbr_lines + 1));
    if (!(*file_content))
    {
        // printf(">>> [parse_content] malloc failed\n");
        return (false);
    }
    // printf(">>> [parse_content] starting to read lines\n");
    while((line = get_next_line(fd)) != NULL)
    {
        // (*file_content)[i] = ft_strdup(line);
        (*file_content)[i] = ft_strtrim(line, "\n");

        if(!(*file_content)[i])
        {
            // printf(">>> [parse_content] strdup failed at line %d\n", i);
            return(clean_2darray(*file_content), false);
        }
        i++;
        free(line);
    }
    (*file_content)[i] = NULL;
    close(fd);

    int j = 0;
    printf("printing initial file data:\n\n");
    while ((*file_content)[j])
    {
        printf("%s\n", (*file_content)[j]);
        j++;
    }
    printf("\n\neof\n\n");
    // printf(">>> [parse_content] finished reading lines\n");
    return(true);
}