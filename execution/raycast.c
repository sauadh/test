#include "../inc/cub3d.h"

static void	init_raycast(t_main_data *main_data, t_player *player, t_ray *ray, double x)
{
	ray->camera_x = (2 * x / main_data->screen_width) - 1;
	ray->side = 0;
	ray->hit = FALSE;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int) player->pos_x;
	ray->map_y = (int) player->pos_y;
	if (ray->dir_x == 0.00)
		ray->deltadist_x = 1e30;
	else
		ray->deltadist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0.00)
		ray->deltadist_y = 1e30;
	else
		ray->deltadist_y = fabs(1 / ray->dir_y);
}


static void	set_side_dist(double posx, double posy, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (posx - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = ((1 - (posx - ray->map_x)) * ray->deltadist_x);
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (posy - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (1 - (posy - ray->map_y)) * ray->deltadist_y;
	}
}

static void do_ray(t_main_data *main_data, t_ray *ray)
{
    while (!ray->hit)
    {
        if (ray->sidedist_x < ray->sidedist_y)
        {
            ray->sidedist_x += ray->deltadist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->sidedist_y += ray->deltadist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        int map_x = (int)ray->map_x;
        int map_y = (int)ray->map_y;

        if (map_y < 0 || map_y >= main_data->map_height)
        {
            printf("Ray map_y out of bounds: %d\n", map_y);
            ray->hit = TRUE;
            break;
        }

        // Check X bounds using actual map line length
        size_t line_len = ft_strlen(main_data->maplines[map_y]);
        if (map_x < 0 || (size_t)map_x >= line_len)
        {
            printf("Ray map_x out of bounds: %d (line length: %zu)\n", map_x, line_len);
            ray->hit = TRUE;
            break;
        }

        // Check if hit wall
        if (main_data->maplines[map_y][map_x] != '0')
            ray->hit = TRUE;
    }
}


int	render(void *param)
{
	
	t_ray	ray;
	t_tex		tex;
	t_main_data		*main_data;
	main_data = (t_main_data *) param;
	movement(main_data);
	flush(*main_data);
	double		x;

	
	x = -1;
	while (++x < main_data->screen_width)
	{

		init_raycast(main_data, &main_data->player, &ray, x);
		set_side_dist(main_data->player.pos_x, main_data->player.pos_y, &ray);
		do_ray(main_data, &ray);
		calculate_wall_height(main_data, &ray);
		set_up_tex_x(main_data, ray, &tex);
		draw_v_line(main_data, ray, x, main_data->floor.in_int);
		draw_v_line(main_data, ray, x, main_data->ceiling.in_int);
		update_render(main_data, &tex, ray, x);

	}
	return (draw_gun_sprite(main_data),
		mlx_put_image_to_window(main_data->mlx, main_data->win,
			main_data->img.image, 0, 0), 0);
}
