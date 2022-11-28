#ifndef __H_FUBOS_ASSERT_H
#define __H_FUBOS_ASSERT_H

/* https://stackoverflow.com/questions/807244/c-compiler-asserts-how-to-implement */

#define GLUE(a,b) __GLUE(a,b)
#define __GLUE(a,b) a ## b
#define CVERIFY(expr, msg) typedef char GLUE (compiler_verify_, msg) [(expr) ? (+1) : (-1)]
#define __ASSERT(exp) CVERIFY (exp, __LINE__)

#define return_val_if(exp, value) if (exp) return value 
#define return_val_if_fail(exp, value) return_val_if(!exp, value)
#define return_if(exp) return_val_if(exp,)

#endif /* __H_FUBOS_ASSERT_H */
