#include "../inc/cub3d.h"

void	rotate_vector(double *x, double *y, double angle)
{
	double	old_x;

	old_x = *x;
	*x = cos(angle) * (*x) - sin(angle) * (*y);
	*y = sin(angle) * old_x + cos(angle) * (*y);
}
void	rotate_left(t_main_data *main_data)
{
	if (!main_data->rot_left)
		return;
	rotate_vector(&main_data->player.dir_x, &main_data->player.dir_y, -ROT_SPEED);
	rotate_vector(&main_data->player.plane_x, &main_data->player.plane_y, -ROT_SPEED);
	main_data->player.dir -= ROT_SPEED;
	if (main_data->player.dir < 0)
		main_data->player.dir += 2 * M_PI;
}

void	rotate_right(t_main_data *main_data)
{
	if (!main_data->rot_right)
		return;
	rotate_vector(&main_data->player.dir_x, &main_data->player.dir_y, ROT_SPEED);
	rotate_vector(&main_data->player.plane_x, &main_data->player.plane_y, ROT_SPEED);
	main_data->player.dir += ROT_SPEED;
	if (main_data->player.dir >= 2 * M_PI)
		main_data->player.dir -= 2 * M_PI;
}

t_bool check_valid_move(t_main_data *data, int key)
{
	t_point target = { data->player.pos_x, data->player.pos_y };
	double dir;
	if (key == W_KEY || key == S_KEY)
	{
		if (key == W_KEY)
		 	dir = 1;
		else
		  	dir = -1;
		target.x += data->player.dir_x * MOVE_SPEED * dir;
		target.y += data->player.dir_y * MOVE_SPEED * dir;
	}
	else if (key == A_KEY || key == D_KEY)
	{
		if (key == D_KEY)
		 	dir = 1;
		else
		  	dir = -1;
		target.x += -data->player.dir_y * MOVE_SPEED * dir;
		target.y +=  data->player.dir_x * MOVE_SPEED * dir;
	}
	else
		return FALSE;

	int tx = (int)target.x;
	int ty = (int)target.y;

	if (ty < 0 || ty >= data->map_height || !data->maplines[ty])
		return FALSE;

	size_t len = ft_strlen(data->maplines[ty]);
	if (tx < 0 || (size_t)tx >= len)
		return FALSE;

	return data->maplines[ty][tx] != '1';
}




void	move_player(t_main_data *data, int key, t_bool *move_flag)
{
	if (*move_flag == FALSE)
		return;

	double move_x = 0;
	double move_y = 0;

	if (key == W_KEY || key == S_KEY)
	{
		double dir = (key == W_KEY) ? 1 : -1;
		move_x = data->player.dir_x * MOVE_SPEED * dir;
		move_y = data->player.dir_y * MOVE_SPEED * dir;
	}
	else if (key == A_KEY || key == D_KEY)
	{
		double dir = (key == D_KEY) ? 1 : -1;
		move_x = -data->player.dir_y * MOVE_SPEED * dir;
		move_y =  data->player.dir_x * MOVE_SPEED * dir;
	}
	else
		return;

	if (check_valid_move(data, key))
	{
		data->player.pos_x += move_x;
		data->player.pos_y += move_y;

		if (data->player.pos_x < 0)
			data->player.pos_x = 0;
		if (data->player.pos_y < 0)
			data->player.pos_y = 0;
	}
}

void movement(t_main_data *data)
{
	move_player(data, W_KEY, &data->move_up);
	move_player(data, S_KEY, &data->move_down);
	move_player(data, A_KEY, &data->move_left);
	move_player(data, D_KEY, &data->move_right);

	rotate_left(data);
	rotate_right(data);
}



