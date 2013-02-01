#ifndef RUMMIKUB_CORE__UTIL_H
#define RUMMIKUB_CORE__UTIL_H

#define MUST_SPECIALIZE(cls_or_func) static_assert( \
    sizeof(cls_or_func*)<0, "template instance of \"" \
    #cls_or_func "\" must be specialized."\
    )

#endif // RUMMIKUB_CORE__UTIL_H

