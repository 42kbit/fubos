#ifndef __H_FUBOS_ASSERT_H
#define __H_FUBOS_ASSERT_H

/* https://stackoverflow.com/questions/807244/c-compiler-asserts-how-to-implement */

#define GLUE(a,b) __GLUE(a,b)
#define __GLUE(a,b) a ## b

#define CVERIFY(expr, msg) typedef char GLUE (compiler_verify_, msg) [(expr) ? (+1) : (-1)]

#define __ASSERT(exp) CVERIFY (exp, __LINE__)

#endif /* __H_FUBOS_ASSERT_H */
