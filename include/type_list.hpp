//
// Created by chazz on 15/05/22.
//

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
            using Head = Hd;
            using Next = Nt;
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
        struct find_first_upper_bound_element_by_size;

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
