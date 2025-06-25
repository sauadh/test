#include "../inc/cub3d.h"

int	ft_destroy(t_main_data *main_data)
{

	mlx_destroy_window(main_data->mlx, main_data->win);
	if (main_data->img.image != NULL)
		mlx_destroy_image(main_data->mlx, main_data->img.image);
	//check leaks
	exit(0);
	return (0);
}

int	key_press_handler(int key, t_main_data *main_data)
{
	if (key == W_KEY)
		main_data->move_up = TRUE;
	else if (key == A_KEY)
		main_data->move_left = TRUE;
	else if (key == S_KEY)
		main_data->move_down = TRUE;
	else if (key == D_KEY)
		main_data->move_right = TRUE;
	else if (key == L_ARROW)
		main_data->rot_left = TRUE;
	else if (key == R_ARROW)
		main_data->rot_right = TRUE;
	else if (key == ESC_KEY)
		ft_destroy(main_data);
	return (0);
}

int	key_release_handler(int key, t_main_data *main_data)
{
	if (key == W_KEY)
		main_data->move_up = FALSE;
	else if (key == A_KEY)
		main_data->move_left = FALSE;
	else if (key == S_KEY)
		main_data->move_down = FALSE;
	else if (key == D_KEY)
		main_data->move_right = FALSE;
	else if (key == L_ARROW)
		main_data->rot_left = FALSE;
	else if (key == R_ARROW)
		main_data->rot_right = FALSE;
	return (0);
}