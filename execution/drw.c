#include "../inc/cub3d.h"

void	flush(t_main_data main_data)
{
	int	x;
	int	y;

	y = 0;
	while (y < main_data.screen_height)
	{
		x = 0;
		while (x < main_data.screen_width)
		{
			my_pixel_put(&main_data, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

int	get_color(t_main_data *main_data
, int index, int tex_x, int tex_y)
{
	int	color;
	int	offset;

	color = 0;
	offset = (main_data->tex[index].tex_width * tex_y) + (tex_x);
	color = *(main_data->tex[index].buff + offset);
	return (color);
}

void	draw_v_line(t_main_data *main_data, t_ray ray, int x, int color)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	if (color == main_data->ceiling.in_int)
	{
		start = 0;
		end = ray.drw_end;
	}
	else if (color == main_data->floor.in_int)
	{
		start = ray.drw_start;
		end = main_data->screen_height - 1;
	}
	while (start < end)
	{
		my_pixel_put(main_data, x, start, color);
		start++;
	}
}

void	my_pixel_put(t_main_data *main_data, int x, int y, int color)
{
	int	offset;

	offset = (main_data->screen_width * y) + x;
	*(offset + main_data->img.buff) = color;
}

static void	draw_gun(t_main_data *game)
{
	int	color;
	int	offset;
	int	x;
	int	y;

	x = 0;
	while (x < game->screen_width - 1)
	{
		y = 0;
		while (y < game->screen_height - 1)
		{
			offset = (game->tex[4].tex_width * y) + x;
			color = *(game->tex[4].buff + offset);
			if (color > 0)
				*(game->img.buff + offset) = color;
			y++;
		}
		x++;
	}
}

static void	draw_cross_hair(t_main_data *game)
{
	int	start;
	int	end;

	start = (game->screen_height / 2) - 20;
	end = (game->screen_height / 2) - 7;
	while (start < end)
		my_pixel_put(game, game->screen_width / 2, start++, 0x39FF14);
	start = (game->screen_height / 2) + 7;
	end = (game->screen_height / 2) + 20;
	while (start < end)
		my_pixel_put(game, game->screen_width / 2, start++, 0x39FF14);
	start = (game->screen_width / 2) - 20;
	end = (game->screen_width / 2) - 7;
	while (start < end)
		my_pixel_put(game, start++, game->screen_height / 2, 0x39FF14);
	start = (game->screen_width / 2) + 7;
	end = (game->screen_width / 2) + 20;
	while (start < end)
		my_pixel_put(game, start++, game->screen_height / 2, 0x39FF14);
}

void	draw_gun_sprite(t_main_data *game)
{
	draw_cross_hair(game);
	draw_gun(game);
}