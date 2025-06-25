#include "../inc/cub3d.h"

void	calculate_wall_height(t_main_data *main_data, t_ray *ray)
{

	if (ray->side == 0)
	{
		ray->sidedist_x -= ray->deltadist_x;
		ray->wall_height = (int)(main_data->screen_height / ray->sidedist_x);
		ray->drw_start = (main_data->screen_height / 2) - (3 * ray->wall_height / 4);
		if (ray->drw_start < 0)
			ray->drw_start = 0;
		ray->drw_end = (main_data->screen_height / 2) + (ray->wall_height / 4);
		if (ray->drw_end > main_data->screen_height)
			ray->drw_end = main_data->screen_height - 1;
	}
	else
	{
		ray->sidedist_y -= ray->deltadist_y;
		ray->wall_height = (int)(main_data->screen_height / ray->sidedist_y);
		ray->drw_start = (main_data->screen_height / 2) - (3 * ray->wall_height / 4);
		if (ray->drw_start < 0)
			ray->drw_start = 0;
		ray->drw_end = (main_data->screen_height / 2) + (ray->wall_height / 4);
		if (ray->drw_end > main_data->screen_height)
			ray->drw_end = main_data->screen_height - 1;
	}
}

void	set_up_tex_x(t_main_data *main_data, t_ray ray, t_tex *tex)
{
	if (ray.side == 0)
	{
		tex->wall_x = main_data->player.pos_y + ray.sidedist_x * ray.dir_y;
		tex->wall_x -= floor(tex->wall_x);
	}
	else
	{
		tex->wall_x = main_data->player.pos_x + ray.sidedist_y * ray.dir_x;
		tex->wall_x -= floor(tex->wall_x);
	}
	tex->tex_x = (int)(tex->wall_x * main_data->tex[0].tex_width);
	if (ray.side == 0 && ray.dir_x < 0)
		tex->tex_x = main_data->tex[0].tex_width - (tex->tex_x + 1);
	if (ray.side == 1 && ray.dir_y > 0)
		tex->tex_x = main_data->tex[0].tex_width - (tex->tex_x + 1);
}

static int	select_index(t_ray ray)
{
	if (ray.side == 0 && ray.dir_x > 0)
		return (2);
	if (ray.side == 0 && ray.dir_x < 0)
		return (3);
	if (ray.side == 1 && ray.dir_y > 0)
		return (1);
	if (ray.side == 1 && ray.dir_y < 0)
		return (0);
	return (-1);
}
void	update_render(t_main_data *main_data, t_tex *tex, t_ray ray, double x)
{
	int	color;
	int	offset;
	int	index;

	index = select_index(ray);
    if (index < 0 || index >= 4)
    {
	    printf("Invalid texture index: %d\n", index);
	    return;
    }

	tex->step = ((double) main_data->tex[index].tex_height / ray.wall_height);
	tex->tex_pos = (ray.drw_start - main_data->screen_height / 2 + 3
			* ray.wall_height / 4) * tex->step;
	while (ray.drw_start < ray.drw_end)
	{
		//tex->tex_y = (int) tex->tex_pos & (main_data->tex[index].tex_height - 1);
        tex->tex_y = (int)tex->tex_pos % main_data->tex[index].tex_height;
        if (tex->tex_y < 0)
	        {tex->tex_y += main_data->tex[index].tex_height;}

		tex->tex_pos += tex->step;
		color = get_color(main_data, index, tex->tex_x, tex->tex_y);
        if (tex->tex_x < 0 || tex->tex_x >= main_data->tex[index].tex_width)
        {
	        printf("Invalid tex_x: %d\n", tex->tex_x);
	        return;
        }
		if (ray.side == 1)
			color = (color >> 1) & 8355711;
		offset = (main_data->screen_width * ray.drw_start) + x;
        if (ray.drw_start < 0 || ray.drw_start >= main_data->screen_height ||
	    x < 0 || x >= main_data->screen_width)
        {
	        printf("Invalid buffer write at x = %f, y = %d\n", x, ray.drw_start);
	        return;
        }
		*(main_data->img.buff + offset) = color;
		ray.drw_start++;
	}
}

