#include "../inc/cub3d.h"

void	init_dir(t_main_data *main_data)
{
	int	x;
	int	y;

	x = main_data->player.pos_x;
	y = main_data->player.pos_y;
	if (main_data->maplines[y][x] == 'N')
		main_data->player.dir = 0;
	else if (main_data->maplines[y][x] == 'E')
		main_data->player.dir = 1.5709;
	else if (main_data->maplines[y][x] == 'S')
		main_data->player.dir = 3.14159;
	else if (main_data->maplines[y][x] == 'W')
		main_data->player.dir = 4.71239;
}

int main(int ac, char **av)
{
    t_main_data main_data;
    char **file_content;
    (void) av;
    file_content = NULL;
    if(ac != 2)
        exit_program("Error: need the path for map file", NULL);
    printf(">>> Stage 1: checking file format\n");
    if(!check_file_format(av[1]))
        exit_program("Error: wrong format file: .cub\n", NULL);
    printf(">>> Stage 2: checking if file can be opened\n");
    if(!valid_file(av[1]))
        exit_program("Error: file   can not be opened\n", NULL);
     printf(">>> Stage 3: parsing content\n");
    if(!parse_content(av[1], &file_content))
        exit_program("Error: invalid content\n", NULL);
    printf(">>> Stage 4: validating content\n");
    if(!valid_content(file_content, &main_data))
         exit_program("Error: invalid content\n", NULL);
    // if (!valid_content(file_content, &main_data))
    // {
    //     printf("hlo1");
    //     // clean(file_content);
    //     // clean_main_data(&main_data);
    //     //exit_program("Error: invalid content\n", NULL);
    // }
    main_data.img.image = mlx_new_image(main_data.mlx,
			main_data.screen_width, main_data.screen_height);
	if (main_data.img.image == NULL)
		return (printf("Error\nCouldn't allocate backdrop img ptr\n"), 1);
	main_data.img.buff = (int *)
		mlx_get_data_addr(main_data.img.image,
			&(main_data.img.bpp), &(main_data.img.l_len),
			&(main_data.img.endian));
	if (main_data.img.buff== NULL)
		return (printf("Error\nCouldn't allocate img pxl ptr\n"), 1);
    init_dir(&main_data);
    // clean(file_content);
    // clean_main_data(&main_data);
    mlx_hook(main_data.win, 2, 1L << 0, key_press_handler, &main_data);
	mlx_hook(main_data.win, 3, 1L << 1, key_release_handler, &main_data);
    mlx_hook(main_data.win, 17, 0, ft_destroy, &main_data);
    mlx_loop_hook(main_data.mlx, render, &main_data);
	mlx_loop(main_data.mlx);
    return(1);
}
