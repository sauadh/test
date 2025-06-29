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

static bool is_valid_tile(t_main_data *main_data, int x, int y)
{
	if (y < 0 || y >= main_data->map_height)
		return false;
	if (x < 0 || x >= (int)ft_strlen(main_data->maplines[y]))
		return false;
	char tile = main_data->maplines[y][x];
	return (tile != '1' && tile != ' ');
}

void try_move(t_main_data *main_data, double dx, double dy)
{
	double new_x = main_data->player.pos_x + dx;
	double new_y = main_data->player.pos_y + dy;
	int f;

	if (dx > 0)
		f = 1;
	else 
		f = -1;
	int check_x = (int)(new_x + COLLISION_RADIUS * f);
	if (dy > 0)
		f = 1;
	else 
		f = -1;
	int check_y = (int)(new_y + COLLISION_RADIUS * f);

	// Check both axes at once — no sliding
	if (is_valid_tile(main_data, check_x, check_y))
	{
		main_data->player.pos_x = new_x;
		main_data->player.pos_y = new_y;
	}
}


void move_up(t_main_data *main_data)
{
    if (!main_data->move_up) return;
    try_move(main_data, main_data->player.dir_x * MOVE_SPEED, main_data->player.dir_y * MOVE_SPEED);
}

void move_down(t_main_data *main_data)
{
    if (!main_data->move_down) return;
    try_move(main_data, -main_data->player.dir_x * MOVE_SPEED, -main_data->player.dir_y * MOVE_SPEED);
}

void move_left(t_main_data *main_data)
{
    if (!main_data->move_left) return;
    try_move(main_data, main_data->player.dir_y * MOVE_SPEED, -main_data->player.dir_x * MOVE_SPEED);
}

void move_right(t_main_data *main_data)
{
    if (!main_data->move_right) return;
    try_move(main_data, -main_data->player.dir_y * MOVE_SPEED, main_data->player.dir_x * MOVE_SPEED);
}


void movement(t_main_data *main_data)
{
	move_up(main_data);
	move_down(main_data);
	move_left(main_data);
	move_right(main_data);
	rotate_left(main_data);
	rotate_right(main_data);
}

