//==================================================================================================
//  File:       arithmetic_traits.hpp
//
//  Summary:    This header defines several private traits types that are used by the various
//              arithmetic traits types, public and private, to implement arithmetic operators.
//==================================================================================================
//
#ifndef LINEAR_ALGEBRA_ARITHMETIC_TRAITS_HPP_DEFINED
#define LINEAR_ALGEBRA_ARITHMETIC_TRAITS_HPP_DEFINED

namespace STD_LA {
namespace detail {
//--------------------------------------------------------------------------------------------------
//- Helper traits for choosing between three traits-type parameters.
//
template<class T1, class T2, class DEF>
struct non_void_traits_chooser;

template<class T1, class DEF>
struct non_void_traits_chooser<T1, void, DEF>
{
    using traits_type = T1;
};

template<class T2, class DEF>
struct non_void_traits_chooser<void, T2, DEF>
{
    using traits_type = T2;
};

template<class DEF>
struct non_void_traits_chooser<void, void, DEF>
{
    using traits_type = DEF;
};


//--------------------------------------------------------------------------------------------------
//- Helper traits for rebinding standard-conformant allocators.
//
template<class A1, class T1>
using rebind_alloc_t = typename allocator_traits<A1>::template rebind_alloc<T1>;


}       //- detail namespace

template<class ET, class OT> constexpr 
bool
result_requires_resize(vector<ET, OT> const&)
{
	return detail::is_resizable_engine_v<ET>;
}

template<class ET, class OT> constexpr 
bool
result_requires_resize(matrix<ET, OT> const&)
{
	return detail::is_resizable_engine_v<ET>;
}
/*
template<class ET, class OT> constexpr 
bool
is_fixed_size(vector<ET,OT> const&)
{
    return vector<ET,OT>::engine_type::is_fixed_size;
}

template<class ET, class OT> constexpr 
bool
is_fixed_size(matrix<ET,OT> const&)
{
    return matrix<ET,OT>::engine_type::is_fixed_size;
}

template<class ET, class OT> constexpr 
bool
is_resizable(vector<ET,OT> const&)
{
    return vector<ET,OT>::engine_type::is_resizable;
}

template<class ET, class OT> constexpr 
bool
is_resizable(matrix<ET,OT> const&)
{
    return matrix<ET,OT>::engine_type::is_resizable;
}
*/
}       //- STD_LA namespace
#endif  //- LINEAR_ALGEBRA_ARITHMETIC_TRAITS_HPP_DEFINED
