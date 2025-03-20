#ifndef MRB_CUTE_H
#define MRB_CUTE_H

#include <cute.h>
#include <mruby.h>
#if MRB_INT_BIT < 64
#error "need 64 bit mruby"
#endif
#include <mruby/variable.h>
#include <mruby/error.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <mruby/string.h>

#endif // MRB_CUTE_H
