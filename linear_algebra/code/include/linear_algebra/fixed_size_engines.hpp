//==================================================================================================
//  File:       fixed_size_engines.hpp
//
//  Summary:    This header defines fixed-size vector and matrix engines.  In this context,
//              fixed-size means that the row and column extents of such objects are known at
//              compile-time, and thus the engines can be made constexpr.
//==================================================================================================
//
#ifndef LINEAR_ALGEBRA_FIXED_SIZE_ENGINES_HPP_DEFINED
#define LINEAR_ALGEBRA_FIXED_SIZE_ENGINES_HPP_DEFINED

namespace STD_LA {
//==================================================================================================
//  Fixed-size, fixed-capacity matrix engine.
//==================================================================================================
//
template<class T, size_t N>
class fs_vector_engine
{
    static_assert(N >= 1);

  public:
    using engine_category = mutable_vector_engine_tag;
    using element_type    = T;
    using value_type      = remove_cv_t<T>;
    using difference_type = ptrdiff_t;
    using size_type       = size_t;
    using const_reference = T const&;
    using reference       = T&;
    using const_iterator  = detail::vector_const_iterator<fs_vector_engine>;
    using iterator        = detail::vector_iterator<fs_vector_engine>;

  public:
    constexpr fs_vector_engine();
    template<class U>
    constexpr fs_vector_engine(initializer_list<U> list);
    constexpr fs_vector_engine(fs_vector_engine&&) noexcept = default;
    constexpr fs_vector_engine(fs_vector_engine const&) = default;

    constexpr fs_vector_engine&     operator =(fs_vector_engine&&) noexcept = default;
    constexpr fs_vector_engine&     operator =(fs_vector_engine const&) = default;

    constexpr const_reference   operator ()(size_type i) const;
    constexpr const_iterator    begin() const noexcept;
    constexpr const_iterator    end() const noexcept;

    static constexpr size_type  capacity() noexcept;
    static constexpr size_type  elements() noexcept;
    static constexpr size_type  size() noexcept;

    constexpr reference     operator ()(size_type i);
    constexpr iterator      begin() noexcept;
    constexpr iterator      end() noexcept;

    constexpr void  swap(fs_vector_engine& rhs) noexcept;
    constexpr void  swap_elements(size_type i, size_type j) noexcept;

  private:
    T   ma_elems[N];
};

template<class T, size_t N> constexpr
fs_vector_engine<T,N>::fs_vector_engine()
{
    if constexpr (is_arithmetic_v<T>)
    {
        for (auto& elem : ma_elems) 
        {
            elem = static_cast<T>(0);
        }
    }
}

template<class T, size_t N> 
template<class U> constexpr
fs_vector_engine<T,N>::fs_vector_engine(initializer_list<U> list)
:   ma_elems()
{
    size_t   count = min(N, static_cast<size_t>(list.size()));
    auto        iter  = list.begin();

    for (size_t i = 0;  i < count;  ++i, ++iter)
    {
        ma_elems[i] = static_cast<T>( *iter);
    }

    if constexpr (is_arithmetic_v<T>)
    {
        if (count < N)
        {
            for (size_t i = count;  i < N;  ++i) 
            {
                ma_elems[i] = static_cast<T>(0);
            }
        }
    }
}

template<class T, size_t N> inline constexpr 
typename fs_vector_engine<T,N>::const_reference
fs_vector_engine<T,N>::operator ()(size_type i) const
{
    return ma_elems[i];
}

template<class T, size_t N> inline constexpr 
typename fs_vector_engine<T,N>::const_iterator
fs_vector_engine<T,N>::begin() const noexcept
{
    return const_iterator(this, 0, N);
}

template<class T, size_t N> inline constexpr 
typename fs_vector_engine<T,N>::const_iterator
fs_vector_engine<T,N>::end() const noexcept
{
    return const_iterator(this, N, N);
}

template<class T, size_t N> inline constexpr 
typename fs_vector_engine<T,N>::size_type
fs_vector_engine<T,N>::capacity() noexcept
{
    return N;
}

template<class T, size_t N> inline constexpr 
typename fs_vector_engine<T,N>::size_type
fs_vector_engine<T,N>::elements() noexcept
{
    return N;
}

template<class T, size_t N> inline constexpr 
typename fs_vector_engine<T,N>::size_type
fs_vector_engine<T,N>::size() noexcept
{
    return N;
}

template<class T, size_t N> inline constexpr 
typename fs_vector_engine<T,N>::reference
fs_vector_engine<T,N>::operator ()(size_type i)
{
    return ma_elems[i];
}

template<class T, size_t N> inline constexpr 
typename fs_vector_engine<T,N>::iterator
fs_vector_engine<T,N>::begin() noexcept
{
    return iterator(this, 0, N);
}

template<class T, size_t N> inline constexpr 
typename fs_vector_engine<T,N>::iterator
fs_vector_engine<T,N>::end() noexcept
{
    return iterator(this, N, N);
}

template<class T, size_t N> inline constexpr 
void
fs_vector_engine<T,N>::swap(fs_vector_engine& rhs) noexcept
{
    if (&rhs != this)
    {
        for (size_t i = 0;  i < N;  ++i)
        {
            detail::la_swap(ma_elems[i], rhs.ma_elems[i]);
        }
    }
}

template<class T, size_t N> inline constexpr 
void
fs_vector_engine<T,N>::swap_elements(size_type i, size_type j) noexcept
{
    detail::la_swap(ma_elems[i], ma_elems[j]);
}


//==================================================================================================
//  Fixed-size, fixed-capacity matrix engine.
//==================================================================================================
//
template<class T, size_t R, size_t C>
class fs_matrix_engine
{
    static_assert(R >= 1);
    static_assert(C >= 1);

  public:
    using engine_category = mutable_matrix_engine_tag;
    using element_type    = T;
    using value_type      = remove_cv_t<T>;
    using difference_type = ptrdiff_t;
    using size_type       = size_t;
    using size_tuple      = tuple<size_type, size_type>;
    using const_reference = element_type const&;
    using reference       = element_type&;
    using const_pointer   = element_type const*;
    using pointer         = element_type*;

  public:
    constexpr fs_matrix_engine();
    template<class U>
    constexpr fs_matrix_engine(initializer_list<U> list);
    constexpr fs_matrix_engine(fs_matrix_engine&&) noexcept = default;
    constexpr fs_matrix_engine(fs_matrix_engine const&) = default;

    constexpr fs_matrix_engine&     operator =(fs_matrix_engine&&) noexcept = default;
    constexpr fs_matrix_engine&     operator =(fs_matrix_engine const&) = default;
    template<class ET2>
    constexpr fs_matrix_engine&     operator =(ET2 const& rhs);

    constexpr const_reference   operator ()(size_type i, size_type j) const;

    constexpr size_type     columns() const noexcept;
    constexpr size_type     rows() const noexcept;
    constexpr size_tuple    size() const noexcept;

    constexpr size_type     column_capacity() const noexcept;
    constexpr size_type     row_capacity() const noexcept;
    constexpr size_tuple    capacity() const noexcept;

    constexpr reference     operator ()(size_type i, size_type j);

    constexpr void      swap(fs_matrix_engine& rhs) noexcept;
    constexpr void      swap_columns(size_type j1, size_type j2) noexcept;
    constexpr void      swap_rows(size_type i1, size_type i2) noexcept;

  private:
    T   ma_elems[R*C];
};

template<class T, size_t R, size_t C> inline constexpr
fs_matrix_engine<T,R,C>::fs_matrix_engine()
:   ma_elems()
{
    if constexpr (is_arithmetic_v<T>)
    {
        for (auto& elem : ma_elems) 
        {
            elem = static_cast<T>(0);
        }
    }
}

template<class T, size_t R, size_t C> 
template<class U> inline constexpr
fs_matrix_engine<T,R,C>::fs_matrix_engine(initializer_list<U> list)
:   ma_elems()
{
    size_t const    total = R*C;
    size_t const    count = std::min(total, (size_t) list.size());
    auto            iter  = list.begin();

    for (size_t i = 0;  i < count;  ++i, ++iter)
    {
        ma_elems[i] = static_cast<T>(*iter);
    }

    if constexpr (is_arithmetic_v<T>)
    {
        if (count < total)
        {
            for (size_t i = count;  i < total;  ++i) 
            {
                ma_elems[i] = static_cast<T>(0);
            }
        }
    }
}

template<class T, size_t R, size_t C> 
template<class ET2> inline constexpr 
fs_matrix_engine<T,R,C>&
fs_matrix_engine<T,R,C>::operator =(ET2 const& rhs)
{
    using src_size_type = typename ET2::size_type;

    if (rhs.size() != size()) 
    {
        throw runtime_error("invalid size");
    }

    src_size_type   si = 0, sj = 0;
    size_type       di = 0, dj = 0;

    for (;  di < rows();  ++di, ++si)
    {
        for (;  dj < columns();  ++dj, ++sj)
        {
            (*this)(di, dj) = rhs(si, sj);
        }
    }

    return *this;
}

template<class T, size_t R, size_t C> inline constexpr 
typename fs_matrix_engine<T,R,C>::const_reference
fs_matrix_engine<T,R,C>::operator ()(size_type i, size_type j) const
{
    return ma_elems[i*C + j];
}

template<class T, size_t R, size_t C> inline constexpr 
typename fs_matrix_engine<T,R,C>::size_type
fs_matrix_engine<T,R,C>::columns() const noexcept
{
    return C;
}

template<class T, size_t R, size_t C> inline constexpr 
typename fs_matrix_engine<T,R,C>::size_type
fs_matrix_engine<T,R,C>::rows() const noexcept
{
    return R;
}

template<class T, size_t R, size_t C> inline constexpr 
typename fs_matrix_engine<T,R,C>::size_tuple
fs_matrix_engine<T,R,C>::size() const noexcept
{
    return size_tuple(R, C);
}

template<class T, size_t R, size_t C> inline constexpr 
typename fs_matrix_engine<T,R,C>::size_type
fs_matrix_engine<T,R,C>::column_capacity() const noexcept
{
    return C;
}

template<class T, size_t R, size_t C> inline constexpr 
typename fs_matrix_engine<T,R,C>::size_type
fs_matrix_engine<T,R,C>::row_capacity() const noexcept
{
    return R;
}

template<class T, size_t R, size_t C> inline constexpr 
typename fs_matrix_engine<T,R,C>::size_tuple
fs_matrix_engine<T,R,C>::capacity() const noexcept
{
    return size_tuple(R, C);
}

template<class T, size_t R, size_t C> inline constexpr 
typename fs_matrix_engine<T,R,C>::reference
fs_matrix_engine<T,R,C>::operator ()(size_type i, size_type j)
{
    return ma_elems[i*C + j];
}

template<class T, size_t R, size_t C> inline constexpr 
void
fs_matrix_engine<T,R,C>::swap(fs_matrix_engine& rhs) noexcept
{
    if (&rhs != this)
    {
        for (size_t i = 0;  i < R*C;  ++i)
        {
            detail::la_swap(ma_elems[i], rhs.ma_elems[i]);
        }
    }
}

template<class T, size_t R, size_t C> inline constexpr 
void
fs_matrix_engine<T,R,C>::swap_columns(size_type j1, size_type j2) noexcept
{
    if (j1 != j2)
    {
        for (size_t i = 0;  i < R;  ++i)
        {
            detail::la_swap(ma_elems[i*C + j1], ma_elems[i*C + j2]);
        }
    }
}

template<class T, size_t R, size_t C> inline constexpr 
void
fs_matrix_engine<T,R,C>::swap_rows(size_type i1, size_type i2) noexcept
{
    if (i1 != i2)
    {
        for (size_t j = 0;  j < C;  ++j)
        {
            detail::la_swap(ma_elems[i1*C + j], ma_elems[i2*C + j]);
        }
    }
}

}       //- STD_LA namespace
#endif  //- LINEAR_ALGEBRA_FIXED_SIZE_ENGINES_HPP_DEFINED
