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

#ifndef BAZAAR_TYPE_LIST_HPP
#define BAZAAR_TYPE_LIST_HPP

#include <cstddef>

namespace bazaar::traits {

    namespace impl {
        struct end_of_list
        {
            end_of_list() = delete;
            end_of_list(const end_of_list&) = delete;
            end_of_list& operator=(const end_of_list&) = delete;
            ~end_of_list() = delete;
        };
        template<typename Hd, typename Nt>
        struct type_list_impl {
            using Head [[maybe_unused]] = Hd;
            using Next [[maybe_unused]] = Nt;
        };
    }

    template<typename Head, typename Next>
    using type_list_t = impl::type_list_impl<Head, Next>;

    using signed_types_list = type_list_t<signed char,
            type_list_t<signed short,
                    type_list_t<signed int,
                            type_list_t<signed long,
                                    type_list_t<signed long long,
                                            impl::end_of_list>>>>>;

    using unsigned_types_list = type_list_t<unsigned char,
            type_list_t<unsigned short,
                    type_list_t<unsigned int,
                            type_list_t<unsigned long,
                                    type_list_t<unsigned long long,
                                            impl::end_of_list>>>>>;

    namespace impl
    {
        template<typename TypeList, std::size_t Size, bool = Size <= sizeof(typename TypeList::Head)>
        struct find_first_upper_bound_element_by_size {};

        template<typename Head, typename Next, std::size_t Size>
        struct find_first_upper_bound_element_by_size<type_list_t<Head, Next>, Size, true>{
            using type = Head;
        };

        template<typename Head, typename Next, std::size_t Size>
        struct find_first_upper_bound_element_by_size<type_list_t<Head, Next>, Size, false> {
            using type = typename find_first_upper_bound_element_by_size<Next, Size>::type;
        };
    }

}

#endif //BAZAAR_TYPE_LIST_HPP
