#ifndef XWIN_H
# define XWIN_H
# include <libft.h>

typedef struct  s_win	t_win;

typedef struct  s_img
{
    t_win		*win;
    void        *img;
    int         width;
    int         height;
    int         bpp;
    int         lsize;
    int         endian;
    char        *addr;
}               t_img;

typedef struct	s_win
{
    void        *ptr;
    void        *win;
	t_point		***matrice;
	t_tab		*tab;
    t_img       *timg;
    void        *img;
	int			width;
	int			height;
	int			projection;
	int			c;
	int			c2;
	int			zoom;
	int			x;
	int			y;
	int			z;
	int			h;
}				t_win;

t_win			*xwin_start(int width, int height, char *name);
t_img			*img_new(t_win *data, int width, int height);
int				key_hook(int k, t_win *e);
int				expose_hook(t_win *e);
void			my_pixel_put_to_image(t_img *img, int x, int y, int color);

#endif
