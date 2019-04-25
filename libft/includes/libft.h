/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 21:02:17 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/25 18:01:32 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdarg.h>

typedef struct		s_list {
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}					t_list;

typedef struct		s_btree {
	char				*data;
	struct s_btree		*left;
	struct s_btree		*right;
}					t_btree;

typedef struct		s_rb_node
{
	int					red;
	int					data;
	char				*text;
	struct s_rb_node	*parent;
	struct s_rb_node	*link[2];
}					t_rbnode;

typedef	struct		s_rb_tree
{
	t_rbnode			*root;
	int					count;
}					t_rbroot;

typedef struct		s_gnl{
	char				*data;
	int					fd;
}					t_gnl;

# define BUFF_SIZE 1000

typedef struct		s_fmt {
	char				flags;
	int					width;
	int					precision;
	char				size;
	char				type;
	void				*data;
	void				*extra;
}					t_fmt;

typedef struct		s_cntrl {
	char				type;
	void				*data;
	size_t				data_size;
	char				neg;
}					t_cntrl;

# define EQ(a, b) ft_strcmp(a, b) == 0
# define DIFF(a, b) ft_strcmp(a, b) < 0
# define B_SET(byte, pos) (((byte) & (1 << (pos))) ? (1) : (0))
# define MS B_SET(fmts->flags, 0)
# define PS B_SET(fmts->flags, 1)
# define SPC B_SET(fmts->flags, 2)
# define HSH B_SET(fmts->flags, 3)
# define ZO B_SET(fmts->flags, 4)
# define L B_SET(fmts->size, 0)
# define H1 B_SET(fmts->size, 1)
# define HH1 B_SET(fmts->size, 2)
# define L1 B_SET(fmts->size, 3)
# define LL1 B_SET(fmts->size, 4)
# define J1 B_SET(fmts->size, 5)
# define Z1 B_SET(fmts->size, 6)
# define DATA (fmts->data)
# define PREC (fmts->precision)
# define WIDTH (fmts->width)
# define TYPE (fmts->type)
# define NEG (((t_cntrl*)(fmts->extra))->neg)

# define TYPES "sSpdDioOuUxXcCfFbreEgG"
# define FLAGS "-+ #0"
# define SIZES "hlLjz"
# define OCTBASE "01234567"
# define HEXBASE "0123456789abcdef"
# define BIGHEXBASE "0123456789ABCDEF"
# define BINBASE "01"

# define ESCCLR		"eoc"
# define BLACKCLR	"black"
# define REDCLR		"red"
# define GREENCLR	"green"
# define YELLOWCLR	"yellow"
# define BLUECLR	"blue"
# define MAGENTACLR	"magenta"
# define CYANCLR	"cyan"
# define WHITECLR	"white"

# define ABS(a) ((a < 0) ? (a = -a) : (a))

void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy (void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_strrev(char *s);
void				ft_putchar(char c);
void				ft_putchar_fd(unsigned char c, int fd);
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_float_result(t_fmt *a, int b, unsigned long long c,\
int *d);
int					ft_min_in_int_arr(int *arr, int len);
void				ft_print_help(char *str, int *i);
int					ft_arr_len(char **arr);
size_t				ft_strlen(const char *str);
size_t				ft_char_in_str(void *s, char c);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_atoi(const char *nptr);
void				ft_int_arr_rev(int *arr, int len);
long long			ft_atol(const char *nptr);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					get_next_line(const int fd, char **line);
int					ft_intlen(long long n);
int					ft_uintlen(unsigned long long n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strdup(const char *s);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat (char *destination, const char *append);
char				*ft_strncat (char *destination, const char *append,\
size_t n);
size_t				ft_strlcat (char *dst, const char *src, size_t n);
char				*ft_strchr (const char *str, int ch);
char				*ft_strrchr (const char *str, int ch);
char				*ft_strstr(const char *strb, const char *stra);
char				*ft_strnstr(const char *hay, const char *needle,\
size_t len);
int					ft_d_strstr(const char *str, const char *needle,\
char stop_symbol);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_orig(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(long long n);
char				*ft_strrev_bin(char **str);
char				*ft_base_convert(char *base_str, unsigned long long nbr);
char				*ft_int_base_convert(char *base_str, unsigned int nbr);
unsigned char		*ft_strrev_num(unsigned char *s, int len);
char				*ft_str_addition(char *first, char *second);
char				*ft_str_mult(char *first, char *second);
char				*ft_power2(int power);
char				*ft_power5(int power);

void				ft_lstadd(t_list **alst, t_list *list);
void				ft_lstadd_last(t_list *alst, t_list *list);
void				ft_lstclear(t_list *lst);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_add_chain_in_linked_list(t_list *where, t_list *what);

t_btree				*ft_btree_create_node(void *item);
void				ft_btree_apply_prefix(t_btree *root, void (*appf)(void *));
void				ft_btree_apply_infix(t_btree *root, void (*applyf)(void *));
void				ft_btree_apply_suffix(t_btree *root, void (*appf)(void *));
void				ft_btree_insert(t_btree **r, void *item, int \
(*cmpf)(void *, void *));
void				*ft_btree_search(t_btree *root, void *data_ref);

/*
** функции красно-черного дерева
*/

int					is_red(t_rbnode *node);
t_rbnode			*rb_single(t_rbnode *root, int dir);
t_rbnode			*rb_double(t_rbnode *root, int dir);
t_rbnode			*make_node(int data, char *text);
int					ft_first_elem(t_rbroot *tree, int data, char *text);
void				ft_color_swap(t_rbnode *q);
t_rbnode			*ft_insert_node(t_rbnode **g_q, int data, char *text,\
t_rbroot *tree);
void				rb_insert2(t_rbroot *tree, int data, char *text, int dir);
int					rb_insert(t_rbroot *tree, int data, char *text);
void				ft_rbtree_del(t_rbroot *tree, int data);
void				ft_rbtree_print(t_rbnode *p);
t_rbnode			*ft_rbtree_datasearch(t_rbroot *root, int data);
void				ft_del_color_change(t_rbnode **p, t_rbnode **s,\
t_rbnode **q);
void				ft_del_remove_el(t_rbnode **f, t_rbnode **q, t_rbnode **p,\
t_rbroot **r);
int					ft_rbtree_to_arr(t_rbnode *node, char **arr, int i);
void				ft_relationships(t_rbnode *parent);
int					ft_rbtree_max(t_rbnode *node);
int					ft_rbtree_min(t_rbnode *node);
void				ft_rb_freetree(t_rbnode *node);
t_rbroot			*ft_rbtree_root_init(void);

/*
** функции принтф
*/
int					ft_printf(const char *a, ...);
int					ft_sprintf(char *a, const char *b, ...);
int					ft_fprintf(int a, const char *b, ...);
void				select_type_group(t_fmt *a, va_list b, int *c);
void				select_fstrings(t_fmt *a, va_list b, int *c);
void				select_fsig_dec(t_fmt *a, va_list b, int *c);
void				select_funsig_dec(t_fmt *a, va_list b, int *c);
void				select_hexoct(t_fmt *a, va_list b, int *c);
void				select_fdoubles(t_fmt *a, va_list b, int *c);
void				select_fextras(t_fmt *a, va_list b, int *c);
void				select_fexpos(t_fmt *a, va_list b, int *c);
void				select_fgs(t_fmt *fmts, va_list ap, int *ch_cntr);
int					read_format_item(const char **a, va_list b, t_fmt *c);
int					fmt_varg_len_set(int *a, va_list b);
int					fmt_type_set(char *a, const char b);
int					fmt_size_set(char *a, const char **b);
const char			*fmt_read_numbers(int *a, const char *b);
int					fmt_flag_set(char *a, const char b);
t_fmt				*fmt_init(char a, void *b);
void				fmt_clear(t_fmt *a);
char				set_bit(char a, char b);
char				s_a_c(char a, char b, char c);
void				ft_printf_putstr(t_fmt *a, int *b);
void				ft_printf_putstr_s(t_fmt *a, int *b);
void				ft_printf_widestr(t_fmt *a, int *b);
void				ft_printf_widechar(unsigned int a, t_fmt *b, int *c, int k);
void				ft_printf_putchar(int a, int *b, int c, t_fmt *d);
int					write_st(int a, const void *b, size_t c, t_cntrl *d);
void				ft_printf_putd(t_fmt *a, int *b);
void				ft_printf_putld(t_fmt *a, int *b);
void				ft_printf_putlld(t_fmt *a, int *b);
void				ft_printf_putu(t_fmt *a, int *b);
void				ft_printf_putlu(t_fmt *a, int *b);
void				ft_printf_putllu(t_fmt *a, int *b);
void				ft_printf_pointers(t_fmt *a, int *b);
void				ft_printf_putbase(t_fmt *a, int *b, char *c, int d);
void				ft_printf_putdbl(t_fmt *a, int *b);
void				ft_printf_putldbl(t_fmt *a, int *b);
void				ft_printf_putexp(t_fmt *a, int *b);
void				ft_printf_putlexp(t_fmt *a, int *b);
void				ft_printf_putg(t_fmt *fmts, int *i);
void				ft_printf_putlg(t_fmt *fmts, int *i);
void				ft_printf_clr_chk(const char **a);

void				ft_show_result(t_fmt *a, char *b, char *c, int *d);
void				ft_show_exp_result(t_fmt *a, char *b, char *c, int *d);
void				ft_show_exp(t_fmt *fmts, char *front, char *tale, int *i);
char				*ft_add_zeroes(char *str, int n, int len_first);
int					ft_width_solver(t_fmt *fmts, char *tale, int g_exp);
void				ft_mad_printer(t_fmt *a, char *b, char *c, int *d);
char				*ft_round_round(t_fmt *a, char *b, char *c);

void				print_fmt_s(t_fmt *a);
void				print_fmt_ls(t_fmt *a);
void				print_fmt_c(t_fmt *a);
void				print_fmt_lc(t_fmt *a);
void				print_fmt_d(t_fmt *a);
void				print_fmt_ld(t_fmt *a);
void				print_fmt_lld(t_fmt *a);
void				print_fmt_u(t_fmt *a);
void				print_fmt_lu(t_fmt *a);
void				print_fmt_llu(t_fmt *a);
void				print_fmt_o(t_fmt *a);
void				print_fmt_lo(t_fmt *a);
void				print_fmt_llo(t_fmt *a);
void				print_fmt_x(t_fmt *a);
void				print_fmt_lx(t_fmt *a);
void				print_fmt_llx(t_fmt *a);
void				print_fmt_f(t_fmt *a);
void				print_fmt_lf(t_fmt *a);
void				print_fmt_p(t_fmt *a);

long long			ft_power(long x, long y);
double				ft_power_float(long x, long y);
int					ft_swap_in_arr(int **arr, int a, int b);
t_rbnode			*ft_rbtree_next(t_rbroot *root, int data);
void				ft_quicksort_lomuto_asc(int *arr, int start, int end);
void				ft_quicksort_lomuto_des(int *arr, int start, int end);
void				ft_bubble_sort(int *arr, int len);
int					ft_arr_mediana(int *arr, int start, int len, int flag);
void				ft_print_int_arr(int *arr, int len);
char				ft_get_last_letter_in_str(char *str);
int					ft_get_type_of_file(char *file_name, char *needle);

#endif
