// Distributed under the MIT License.
// See LICENSE.txt for details.

/// \file
/// Defines class template BlockNeighbor.

#pragma once

#include <iosfwd>
#include <pup.h>

#include "Domain/Direction.hpp"
#include "Domain/Orientation.hpp"

/// \ingroup ComputationalDomain
/// Information about the neighbor of a Block in a particular direction.
///
/// \tparam VolumeDim the volume dimension.
template <size_t VolumeDim>
class BlockNeighbor {
 public:
  BlockNeighbor() = default;

  /// Construct with the Id and orientation of the neighbor.
  ///
  /// \param id the Id of the neighbor.
  /// \param orientation the Orientation of the neighbor.
  BlockNeighbor(size_t id, Orientation<VolumeDim> orientation);
  ~BlockNeighbor() = default;
  BlockNeighbor(const BlockNeighbor<VolumeDim>& neighbor) = default;
  BlockNeighbor(BlockNeighbor<VolumeDim>&&) noexcept = default;
  BlockNeighbor<VolumeDim>& operator=(const BlockNeighbor<VolumeDim>& rhs) =
      default;
  BlockNeighbor<VolumeDim>& operator=(BlockNeighbor<VolumeDim>&&) noexcept =
      default;

  size_t id() const noexcept { return id_; }

  const Orientation<VolumeDim>& orientation() const noexcept {
    return orientation_;
  }

  // Serialization for Charm++
  void pup(PUP::er& p);  // NOLINT

 private:
  size_t id_{0};
  Orientation<VolumeDim> orientation_;
};

/// Output operator for BlockNeighbor.
template <size_t VolumeDim>
std::ostream& operator<<(std::ostream& os,
                         const BlockNeighbor<VolumeDim>& block_neighbor);

template <size_t VolumeDim>
bool operator==(const BlockNeighbor<VolumeDim>& lhs,
                const BlockNeighbor<VolumeDim>& rhs) noexcept;

template <size_t VolumeDim>
bool operator!=(const BlockNeighbor<VolumeDim>& lhs,
                const BlockNeighbor<VolumeDim>& rhs) noexcept;
