// Distributed under the MIT License.
// See LICENSE.txt for details.

#include <catch.hpp>

#include "Domain/ElementId.hpp"
#include "Utilities/ConstantExpressions.hpp"
#include "tests/Unit/TestHelpers.hpp"

SPECTRE_TEST_CASE("Unit.Domain.ElementId", "[Domain][Unit]") {
  // Test default constructor:
  ElementId<3> test_id;
  CHECK(test_id.block_id() == std::numeric_limits<size_t>::max());
  CHECK(test_id.segment_ids() == make_array<3>(SegmentId()));

  // Test retrieval functions:
  auto segment_ids = std::array<SegmentId, 3>(
      {{SegmentId(2, 3), SegmentId(1, 0), SegmentId(1, 1)}});
  ElementId<3> block_2_3d(2, segment_ids);
  CHECK(block_2_3d.block_id() == 2);
  CHECK(block_2_3d.segment_ids() == segment_ids);

  // Test parent and child operations:
  ElementId<3> id = block_2_3d;
  for (size_t dim = 0; dim < 3; dim++) {
    CHECK(id == id.id_of_child(dim, Side::Lower).id_of_parent(dim));
    CHECK(id == id.id_of_child(dim, Side::Upper).id_of_parent(dim));
    if (0 == gsl::at(id.segment_ids(), dim).index() % 2) {
      CHECK(id == id.id_of_parent(dim).id_of_child(dim, Side::Lower));
    } else {
      CHECK(id == id.id_of_parent(dim).id_of_child(dim, Side::Upper));
    }
  }

  // Test equality operator:
  ElementId<3> element_one(1);
  ElementId<3> element_two(1);
  ElementId<3> element_three(2);
  ElementId<3> element_four(4);
  CHECK(element_one == element_two);
  CHECK(element_two != element_three);
  CHECK(element_two != element_four);
  CHECK(element_three != block_2_3d);

  // Test pup operations:
  CHECK(element_one == serialize_and_deserialize(element_one));

  // Test output operator:
  CHECK(get_output(block_2_3d) == "[B2,(L2I3,L1I0,L1I1)]");
}
