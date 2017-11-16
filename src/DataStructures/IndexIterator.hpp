// Distributed under the MIT License.
// See LICENSE.txt for details.

/// \file
/// Defines IndexIterator.

#pragma once

#include "DataStructures/Index.hpp"

/// \ingroup DataStructures
/// IndexIterator iterates over a unique set of Index.
///
/// \example
/// \snippet Test_IndexIterator.cpp index_iterator_example
///
/// Each integer of the Index will vary from 0 to extents[d] - 1,
/// with the lowest dimension varying the fastest.
template <std::size_t Dim>
class IndexIterator {
 public:
  /// Construct from an Index
  explicit IndexIterator(Index<Dim> extents);
  /// It does not make sense to default construct an IndexIterator
  IndexIterator() = delete;
  /// \cond HIDDEN_SYMBOLS
  ~IndexIterator() = default;
  // @{
  /// No copy or move semantics
  IndexIterator(const IndexIterator<Dim>&) = delete;
  IndexIterator(IndexIterator<Dim>&&) = delete;
  IndexIterator<Dim>& operator=(const IndexIterator<Dim>&) = delete;
  IndexIterator<Dim>& operator=(IndexIterator<Dim>&&) = delete;
  // @}
  /// \endcond

  /// Returns false if the end of the Index iteration is reached
  explicit operator bool() const noexcept { return valid_; }

  /// Advance to next Index.
  IndexIterator<Dim>& operator++();

  decltype(auto) operator*() const noexcept { return index_; }

  /// Returns an index representing the (i, j, ...)th values that the iterator
  /// currently represents
  const Index<Dim>& operator()() const noexcept { return index_; }

  /// Get the offset into a 1D array whose first dimension is assumed to vary
  /// fastest
  size_t offset() const noexcept { return offset_; }

 private:
  const Index<Dim> extents_{};
  Index<Dim> index_{};
  size_t offset_{0};
  bool valid_{false};
};
