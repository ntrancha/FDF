#ifndef DRAW_H
# define DRAW_H

int     droite(t_win *data, t_point *p1, t_point *p2, int color);
void    create_parallele(t_point *p, t_tab *tab, int c, int l, t_win *data);
void    parallele_next(t_point *p, t_tab *tab, t_win *data, int val, int zoom);
void    create_iso(t_point *p, t_tab *tab, int c, int c2, t_win *data);

#endif
