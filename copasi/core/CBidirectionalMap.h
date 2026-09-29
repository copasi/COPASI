// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#pragma once

#include <array>
#include <utility>
#include <algorithm>
#include <string_view>
#include <type_traits>

// A simple aggregate node to replace std::pair and prevent CTAD failures
// Inject key/value traits into MapNode so the deduction guide can inspect them
template < typename K, typename V >
struct MapNode
{
  using KeyType = K;
  using ValueType = V;
  KeyType Key;
  ValueType Value;

  constexpr MapNode()
    : Key()
    , Value()
  {}

  constexpr MapNode(const KeyType & k, const ValueType & v)
    : Key(k)
    , Value(v)
  {}
};

// Helper concept to detect if a type is a character pointer or literal array
template < typename T >
concept IsCharPtr = std::is_convertible_v< T, std::string_view > && (std::is_same_v< std::decay_t< T >, const char * > || std::is_same_v< std::decay_t< T >, char * >);

// Helper metafunction to resolve a type to either std::string_view or itself
template < typename T >
using MapIfChar_t = std::conditional_t< IsCharPtr< T >, std::string_view, T >;

#ifndef SWIG
// Deduction guide handling both template parameters independently
template < typename K, typename V >
MapNode(K, V) -> MapNode< MapIfChar_t< K >, MapIfChar_t< V > >;
#endif // SWIG

template < typename K, typename V, std::size_t N >
class CBidirectionalMap
{
public:
  using MapType = MapNode< K, V >;
  using KeyType = MapType::KeyType;
  using ValueType = MapType::ValueType;

  constexpr static size_t Size = N;

  // Helper to sort by the Key element (Key -> Value)
  constexpr auto sortByKey(std::array< MapNode< K, V >, N > arr)
  {
    std::sort(arr.begin(), arr.end(), [](const auto & a, const auto & b) {return a.Key < b.Key; });
    return arr;
  }

  // Helper to sort by the Value element (Value -> Key)
  constexpr auto sortByValue(std::array< MapNode< K, V >, N > arr)
  {
    std::sort(arr.begin(), arr.end(), [](const auto & a, const auto & b) {return a.Value < b.Value; });
    return arr;
  }

  template <typename F, typename... Ts>
  constexpr auto map_to_array(F&& f, Ts&&... args) {
      using CommonType = std::common_type_t<std::decay_t<std::invoke_result_t<F, Ts>>...>;
      return std::array<CommonType, sizeof...(Ts)>{{f(std::forward<Ts>(args))... } };
  }

  template < typename A >
  constexpr static bool contains(const A & a, const A::value_type & v)
  {
    return std::any_of(a.begin(), a.end(), [v](const A::value_type & k) {return k == v;});
  }

  constexpr KeyType key(const MapType & m) {return m.Key;}
  constexpr ValueType value(const MapType & m) {return m.Value;}

  template < typename T >
  constexpr auto sortArray(std::array< T, Size > arr)
    {
      std::sort(arr.begin(), arr.end());
      return arr;
    }

  constexpr CBidirectionalMap(const std::array< MapType, Size > & map, const std::array< KeyType, Size > & keys, const std::array< ValueType, Size > & values)
    : _array(map)
    , _keys(sortArray(std::array< KeyType, Size >(keys)))
    , _values(sortArray(std::array< ValueType, Size >(values)))
  {}

  // Accepts the unpacked Nodes and constructs the flat arrays smoothly
  template < typename... Nodes >
  constexpr CBidirectionalMap(Nodes &&... nodes)
    : _array({std::forward< Nodes >(nodes)...})
    , _keys(sortArray(std::array< KeyType, Size >({key(std::forward< Nodes >(nodes))... })))
    , _values(sortArray(std::array< ValueType, Size >({value(std::forward< Nodes >(nodes))... })))
  {}

  template < size_t __N >
  constexpr auto subset(const std::array< KeyType, __N > & keys) const
  {
    // Directly maps keys into a perfectly sized new CBidirectionalMap instance
    const auto filtered = filterNodes(keys);
    return CBidirectionalMap< KeyType, ValueType, __N >(filtered.first, keys, filtered.second);
  }

  const V * findByKey(const K & key) const
  {
    for (const auto & Node : _array)
      if (Node.Key == key)
        return &Node.Value;

    return nullptr;
  }

  const K * findByValue(const V & value) const
  {
    for (const MapType & Node : _array)
      if (Node.Value == value)
        return &Node.Key;

    return nullptr;
  }

  constexpr bool containsKey(const K & key) const
  {
    return contains(_keys, key);
  }

  constexpr bool containsValue(const V & value) const
  {
    return contains(_values, value);
  }

  constexpr const std::array< K, N > & keys() const
  {
    return _keys;
  }

  constexpr const std::array< V, N > & values() const
  {
    return _values;
  }

private:
  // Helper to find and return the full MapNode structure by Key at compile-time
  template < size_t __N >
  constexpr auto filterNodes(const std::array< KeyType, __N > & keys) const
  {
    std::array< MapType, __N > Nodes;
    std::array< ValueType, __N > Values;

    auto itNode = Nodes.begin();
    auto itValue = Values.begin();

    for (const auto& node : _array)
      for (const auto & key: keys)
        if (node.Key == key)
          {
            *itNode++ = node;
            *itValue++ = node.Value;
          }

    return std::make_pair(Nodes, Values);
  }

  const std::array< MapType, N > _array;
  const std::array< KeyType, N > _keys;
  const std::array< ValueType, N > _values;
};

// Custom deduction guide based on the lightweight MapNode aggregate type
template < typename... Nodes,
           typename K = std::common_type_t< typename std::decay_t< Nodes >::KeyType... >,
           typename V = std::common_type_t< typename std::decay_t< Nodes >::ValueType... > >
CBidirectionalMap(Nodes...) -> CBidirectionalMap< K, V, sizeof...(Nodes) >;
