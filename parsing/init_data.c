#include "../inc/cub3d.h"
void	init_player(t_player *player)
{
	player->dir = 0.0;
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	player->player = 0;
}

bool init_main_data(t_main_data *main_data)
{
    int i = 0;

    //init textures
    while (i < 4)
    {
		main_data->tex[i].img = NULL;
        main_data->textures[i].path = NULL;
        main_data->textures[i].type = i; // 0 - NO, 1 - SO, 2 - WE, 3 - EA
        i++;
    }
	main_data->floor.red = -1;
	main_data->floor.green = -1;
	main_data->floor.blue = -1;
	main_data->floor.is_set = false;
	main_data->floor.in_int = -1;
	main_data->ceiling.is_set = false;
	main_data->ceiling.red = -1;
	main_data->ceiling.green = -1;
	main_data->ceiling.blue = -1;
	main_data->ceiling.in_int = -1;
	init_player(&main_data->player);
	main_data->player.pos_x = -1;
	main_data->player.pos_y = -1;
	main_data->map_height = 0;
	main_data->screen_height = WIN_H;
	main_data->screen_width = WIN_W;
	main_data->mlx = mlx_init();
	main_data->win = mlx_new_window(main_data->mlx, main_data->screen_width, main_data->screen_height, "cub3d");
	main_data->map_width = 0;
	main_data->maplines = NULL;
	main_data->move_up = FALSE;
	main_data->move_down = FALSE;
	main_data->move_right = FALSE;
	main_data->move_left = FALSE;
	main_data->rot_left = FALSE;
	main_data->rot_right = FALSE;
    return (true);
}

    // Проверка после инициализации
    // i = 0;
    // while (i < 4)
    // {
    //     printf("Texture %d: type = %d, path = %s\n",
    //             i,
    //             data->textures[i].type,
    //             data->textures[i].path);
    //     i++;
    // }

    void	init_dir_player(t_main_data *main_data)
    {
        int x;
		int y;

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
