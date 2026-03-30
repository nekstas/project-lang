#pragma once

#define DIAG_REPORT(ctx, diag_cls, ...) \
    (ctx).diag.template Report<diag_cls>(*this, __VA_ARGS__)
#define DIAG_REPORT_IF(condition, ctx, diag_cls, ...) \
    do {                                              \
        if (condition) {                              \
            DIAG_REPORT(ctx, diag_cls, __VA_ARGS__);  \
        }                                             \
    } while (false)
