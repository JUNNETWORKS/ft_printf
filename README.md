# ft_printf

## メモ

```bash
gcc -c ft_printf_tmp.c -o ft_printf_tmp.o
make -C ./libft
cp libft/libft.a libftprintf.a
ar rcs libftprintf.a ft_printf_tmp.o
nm -s libftprintf.a
gcc -g main_tmp.c libftprintf.a
```
