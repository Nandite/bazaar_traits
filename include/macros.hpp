// Copyright (c) 2022 Papa Libasse Sow.
// https://github.com/Nandite/bazaar_traits
// Distributed under the MIT Software License (X11 license).
//
// SPDX-License-Identifier: MIT
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of
// the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef MACROS_HPP
#define MACROS_HPP

#ifndef __has_feature
#define __has_feature(__x) 0
#endif
// '__is_identifier' returns '0' if '__x' is a reserved identifier provided by
// the compiler and '1' otherwise.
#ifndef __is_identifier
#define __is_identifier(__x) 1
#endif
#define __has_keyword(__x) !(__is_identifier(__x))

#ifndef __has_builtin
#define __has_builtin(__x) 0
#endif

#ifdef __has_builtin
# ifdef __is_identifier
// Intel and older Clang require !__is_identifier for some built-ins:
#  define BZT_HAS_BUILTIN(__x) __has_builtin(__x) || ! __is_identifier(__x)
# else
#  define BZT_HAS_BUILTIN(__x) __has_builtin(__x)
# endif
#endif

#if defined(__GNUC__)
#  define IS_COMPILER_GCC
#endif


#endif //MACROS_HPP
