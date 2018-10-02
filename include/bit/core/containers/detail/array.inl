#ifndef BIT_CORE_CONTAINERS_DETAIL_ARRAY_INL
#define BIT_CORE_CONTAINERS_DETAIL_ARRAY_INL

template<typename T, typename...Args>
inline constexpr bit::core::detail::array_return_type_t<T,Args...>
  bit::core::make_array( Args&&...args )
  noexcept
{
  return { std::forward<Args>(args)... };
}

struct bit::core::detail::to_array_impl
{
  template<typename T, std::size_t N, std::size_t...Idxs>
  static constexpr std::array<T,N> invoke( const T(&array)[N], std::index_sequence<Idxs...> )
    noexcept( std::is_nothrow_copy_constructible<T>::value )
  {
    return { array[Idxs]... };
  }

  template<typename T, std::size_t N, std::size_t...Idxs>
  static constexpr std::array<T,N> invoke( T(&&array)[N], std::index_sequence<Idxs...> )
    noexcept( std::is_nothrow_move_constructible<T>::value )
  {
    return { std::move(array[Idxs])... };
  }
};

template<typename T, std::size_t N>
inline constexpr std::array<T,N> bit::core::to_array( const T(&array)[N] )
  noexcept( std::is_nothrow_copy_constructible<T>::value )
{
  return detail::to_array_impl::invoke( array, std::make_index_sequence<N>() );
}

template<typename T, std::size_t N>
inline constexpr std::array<T,N> bit::core::to_array( T(&&array)[N] )
  noexcept( std::is_nothrow_move_constructible<T>::value )
{
  return detail::to_array_impl::invoke( array, std::make_index_sequence<N>() );
}


#endif /* BIT_CORE_CONTAINERS_DETAIL_ARRAY_INL */
