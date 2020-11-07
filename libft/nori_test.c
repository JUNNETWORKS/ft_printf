#include "libft.h"
#include <stdio.h>

char    *ft_strtrim(char const *s1, char const *set)
{
    size_t    i;
    size_t    k;
    size_t    len;
    char    *ret;
    int        used[256];

    i = 0;
    if (!s1 || !set)
        return (!s1 ? NULL : ft_strdup(s1));
    while (i < 256)
        used[i++] = 0;
    len = ft_strlen(set);
    while (len--)
        used[(int)*set++] += 1;
    i = 0;
    k = 0;
    len = ft_strlen(s1);
    while (used[(int)*(s1 + i)] && s1[i])
        i++;
    while (used[(int)*(s1 + len - k - 1)] && s1[i])
        k++;
    printf("%zu", i);
    if (!(ret = malloc(len - i - k + 1)))
        return (NULL);
    ft_strlcpy(ret, s1 + i, len - i - k + 1);
    return (ret);
}

int main()
{
    char *ret;
    char *ret2;
    int i = 0;

    while (i++ < 10)
    {
        ret = ft_strtrim("", "");
        ret2 = ft_strtrim("aaaaaaaadaaaaasfaaaaaaaa", "aa");
        printf("%s\n", ret);
        printf("%s\n", ret2);
        free(ret);
        free(ret2);
    }
}
