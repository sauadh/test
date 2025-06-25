/*# define WIN_W 960
# define WIN_W 720 */

/*# define WIN_W 1920
# define WIN_W 1080 */
# define WIN_W 1280
# define WIN_H 720

# define MOVE_SPEED 0.08
# define ROT_SPEED	0.05

# define DIM 64

# define OG		"\033[0m"
# define RED	"\033[1;31m"
# define GRN	"\033[1;32m"
# define YLW	"\033[1;33m"
# define BLU	"\033[1;34m"
# define PRL	"\033[0;35m"

//Mac_OS
// # define W_KEY 13
// # define A_KEY 0
// # define S_KEY 1
// # define D_KEY 2
// # define ESC_KEY 53
// # define L_ARROW 123
// # define R_ARROW 124

// Linux
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define ESC_KEY 65307
# define L_ARROW 65361
# define R_ARROW 65363

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif



typedef enum e_type_textr
{
    NO = 0,
    SO = 1,
    WE,
    EA, 
    F,
    C
} t_type_textr;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

// typedef enum e_map_digit{
//     ZERO = 0, 
//     ONE,
//     PLAYER , 
//     SPACE
// } t_map_digit;

typedef struct s_texture
{
    t_type_textr type;
    char *path;
} t_texture;

typedef enum s_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;
typedef struct s_image
{
	void	*image;
	int *buff;
	int		bpp;
	int		l_len;
	int		endian;
}	t_image;

typedef struct s_tex {
	void	*img;
	int		*buff;
	int		tex_width;
	int		tex_height;
	int		bpp;
	int		l_len;
	int		endian;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	double	step;
}				t_tex;
typedef struct s_rgb 
{
    int red;
    int green; 
    int blue;
	long long int in_int;
    bool is_set;
} t_rgb;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	double		map_x;
	double		map_y;
	int		step_x;
	int		step_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	int		side;
	bool	hit;
	int		wall_height;
	int		drw_start;
	int		drw_end;
}	t_ray;

typedef struct s_player
{
	double	dir;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int	 player;
}	t_player;

typedef struct s_main_data
{
    t_texture textures[4];
	t_tex     tex[5];
    t_rgb floor;
    t_rgb ceiling;
    void	*mlx;
	void	*win;
	t_image	img;
	t_ray  ray;
	t_bool		move_up;
	t_bool		move_down;
	t_bool		move_right;
	t_bool		move_left;
	t_bool		rot_right;
	t_bool		rot_left;
	int    screen_height;
	int    screen_width;
    // t_map_digit **map;
	int n_player;//check with diana
    t_image	n_xpm;
	t_image	e_xpm;
	t_image	w_xpm;
	t_image	s_xpm;
    char	**maplines;
	int		map_height;
	int		map_width;
    t_player    player;//change in parsing 
    float   direction;  

    
} t_main_data;