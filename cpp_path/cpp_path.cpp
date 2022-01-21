

//#ifndef _EASTL
//#define _EASTL  ‘› ±≤ª”√EASTL
//#endif

#include "cpp_path.hpp"

extern "C" size_t
path_sanitize(char *s, size_t sz, const char *base, const char *expr)
{
    apathy::stlx::string t("");

    t.append(base);
    if (expr[0] == '.')
    {
        t.append("\\");
    }

    t.append(expr);
    for (char &c : t)
    {
        if (c == '\\')
            c = '/';
    }

    apathy::Path path(t);
    t = path.sanitize().string();

    if (t.empty())
        return 0;

    for (char &c : t)
    {
        if (c == '/')
            c = '\\';
    }

    //  \\??\\

    char c_tmp[] = {'\\', '?', '?', '\\', 0};

    t.insert(0, c_tmp);

    size_t size = t.size();
    const char *ptr = t.c_str();

    if (sz < size + 1)
        return 0;

    memcpy(s, ptr, size);
    s[size] = '\0';

    return size;
}
