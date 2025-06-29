#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include <fcntl.h>
#include "parsing.h"
# include <math.h>
# include "mlx.h"


//validation
bool check_file_format(char *input);
bool valid_file(char *input);
bool is_empty_line(char *str);
bool parse_content(char *input, char ***file_content); 
void clean(char **content);
void clean_2darray(char **content);
void clean_main_data(t_main_data *data);
void exit_program(char *message, void *data);
bool valid_content(char **file_content, t_main_data *main_data);
bool init_main_data(t_main_data *main_data);
void free_split(char **split);
bool validate_textures(char *file_content, t_main_data *main_data);
int get_index(const char *str);
char *skip_tab_spaces(char *line);
char *skip_digits(char *line);
char *skip_comma(char *line);
char *skip_empty_lines(int fd);
char *set_color_value(char *line, int *value, bool is_coma);
bool validate_colors(char *file_content, t_main_data *main_data);
bool parse_map(char **map_lines, int j, t_main_data *main_data);
bool validate_map(t_main_data *main_data);
bool find_player(t_main_data *main_data);
void  init_dir_player(t_main_data *main_data);
void	exit_err(t_main_data *game, char *line, char *message);
t_bool	is_wspace(char c);
void	whitespace_checker(t_main_data *game, char *trimmed);
void	parse_elements(t_main_data *game, int fd);

int	render(void *param);


int	key_press_handler(int key, t_main_data *main_data);
int	key_release_handler(int key,t_main_data *main_data);

void	calculate_wall_height(t_main_data *main_data, t_ray *ray);
void	set_up_tex_x(t_main_data *main_data, t_ray ray, t_tex *tex);

void	update_render(t_main_data *main_data, t_tex *tex, t_ray ray, double x);
void	my_pixel_put(t_main_data *main_data, int x, int y, int color);
void	draw_ceiling_and_floor(t_main_data *main_data, t_ray ray, double x);

void	draw_gun_sprite(t_main_data *game);
void	draw_v_line(t_main_data *main_data, t_ray ray, int x, int color);
int	get_color(t_main_data *main_data, int index, int tex_x, int tex_y);
void	flush(t_main_data main_data);

int	    ft_destroy(t_main_data *main_data);
void	movement(t_main_data *main_data);