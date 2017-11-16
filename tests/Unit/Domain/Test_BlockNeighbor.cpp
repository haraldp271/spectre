// Distributed under the MIT License.
// See LICENSE.txt for details.

#include <catch.hpp>

#include "Domain/BlockNeighbor.hpp"
#include "tests/Unit/TestHelpers.hpp"

SPECTRE_TEST_CASE("Unit.Domain.BlockNeighbor", "[Domain][Unit]") {
  // Test default constructor, only used for Charm++ serialization so no CHECK
  // calls:
  BlockNeighbor<3> test_block_neighbor;

  // Test constructor:
  Orientation<3> custom_orientation(std::array<Direction<3>, 3>{
      {Direction<3>::upper_eta(), Direction<3>::upper_zeta(),
       Direction<3>::upper_xi()}});
  BlockNeighbor<3> custom_neighbor(0, custom_orientation);
  CHECK(custom_neighbor.id() == 0);
  CHECK(custom_neighbor.orientation().mapped(Direction<3>::upper_xi()) ==
        Direction<3>::upper_eta());
  CHECK(custom_neighbor.orientation().mapped(Direction<3>::upper_eta()) ==
        Direction<3>::upper_zeta());
  CHECK(custom_neighbor.orientation().mapped(Direction<3>::upper_zeta()) ==
        Direction<3>::upper_xi());

  // Test output operator:
  CHECK(get_output(custom_neighbor) == "Id = 0; orientation = (+1, +2, +0)");

  // Test comparison operator:
  CHECK(test_block_neighbor != custom_neighbor);
  CHECK(custom_neighbor == custom_neighbor);

  // Test serialization:
  CHECK(custom_neighbor == (serialize_and_deserialize(custom_neighbor)));

  // Test semantics:
  const auto custom_copy = custom_neighbor;
  test_copy_semantics(custom_neighbor);
  test_move_semantics(std::move(custom_neighbor), custom_copy);
}
