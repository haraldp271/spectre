// Distributed under the MIT License.
// See LICENSE.txt for details.

#include <catch.hpp>

#include "Utilities/ConstantExpressions.hpp"
#include "Utilities/TypeTraits.hpp"
#include "tests/Unit/TestHelpers.hpp"

namespace {
template <typename T>
struct TestTwoToThe {
  static constexpr T zero = 0;
  static constexpr T one = 1;
  static constexpr T two = 2;
  static constexpr T three = 3;
  static constexpr T four = 4;
  static constexpr T eight = 8;
  static constexpr T sixteen = 16;

  static_assert(one == two_to_the(zero),
                "Failed test Unit.Utilities.ConstantExpressions");
  static_assert(two == two_to_the(one),
                "Failed test Unit.Utilities.ConstantExpressions");
  static_assert(four == two_to_the(two),
                "Failed test Unit.Utilities.ConstantExpressions");
  static_assert(eight == two_to_the(three),
                "Failed test Unit.Utilities.ConstantExpressions");
  static_assert(sixteen == two_to_the(four),
                "Failed test Unit.Utilities.ConstantExpressions");
};

template struct TestTwoToThe<unsigned int>;
template struct TestTwoToThe<unsigned short>;
template struct TestTwoToThe<unsigned long>;
template struct TestTwoToThe<unsigned long long>;

// [[OutputRegex, two_to_the is overflowing!]]
[[noreturn]] SPECTRE_TEST_CASE("Unit.Utilities.ConstantExpressions.TwoToThe",
                               "[Unit][Utilities]") {
  ASSERTION_TEST();
#ifdef SPECTRE_DEBUG
  const size_t n = 8 * sizeof(size_t);
  // clang-tidy: value stored ... never used
  const size_t two_to_the_n = two_to_the(n);  // NOLINT
  ERROR("Failed to trigger ASSERT in an assertion test");
#endif
}

static_assert(square(2) == 4, "Failed test Unit.Utilities.ConstantExpressions");

static_assert(cube(2) == 8, "Failed test Unit.Utilities.ConstantExpressions");

static_assert(get_nth_bit(0, 0) == 0,
              "Failed test Unit.Utilities.ConstantExpressions");
static_assert(get_nth_bit(1, 0) == 1,
              "Failed test Unit.Utilities.ConstantExpressions");
static_assert(get_nth_bit(2, 0) == 0,
              "Failed test Unit.Utilities.ConstantExpressions");
static_assert(get_nth_bit(2, 1) == 1,
              "Failed test Unit.Utilities.ConstantExpressions");
static_assert(get_nth_bit(4, 2) == 1,
              "Failed test Unit.Utilities.ConstantExpressions");

// Test pow<>
static_assert(pow<4>(2.0) == 16.0, "Failed testing pow");
static_assert(pow<0>(2.0) == 1.0, "Failed testing pow");
static_assert(pow<-4>(2.0) == 1.0 / 16.0, "Failed testing pow");

// Test abs
static_assert(constexpr_abs(0) == 0, "Failed testing abs");
static_assert(constexpr_abs(1.4) == 1.4, "Failed testing abs");
static_assert(constexpr_abs(-1.4) == 1.4, "Failed testing abs");

// Test max_by_magnitude
static_assert(max_by_magnitude(1, 2) == 2, "Failed testing max_by_magnitude");
static_assert(max_by_magnitude(2, 1) == 2, "Failed testing max_by_magnitude");
static_assert(max_by_magnitude(-1, 2) == 2, "Failed testing max_by_magnitude");
static_assert(max_by_magnitude(2, -1) == 2, "Failed testing max_by_magnitude");
static_assert(max_by_magnitude(1, -2) == -2, "Failed testing max_by_magnitude");
static_assert(max_by_magnitude(-2, 1) == -2, "Failed testing max_by_magnitude");
static_assert(max_by_magnitude(-1, -2) == -2,
              "Failed testing max_by_magnitude");
static_assert(max_by_magnitude(-2, -1) == -2,
              "Failed testing max_by_magnitude");
static_assert(max_by_magnitude({-2, -1, -3}) == -3,
              "Failed testing max_by_magnitude");
static_assert(max_by_magnitude(1, -1) == 1,
              "Failed testing max_by_magnitude");
static_assert(max_by_magnitude(-1, 1) == -1,
              "Failed testing max_by_magnitude");
static_assert(max_by_magnitude({1, -1}) == 1,
              "Failed testing max_by_magnitude");
static_assert(max_by_magnitude({-1, 1}) == -1,
              "Failed testing max_by_magnitude");

// Test min_by_magnitude
static_assert(min_by_magnitude(1, 2) == 1, "Failed testing min_by_magnitude");
static_assert(min_by_magnitude(2, 1) == 1, "Failed testing min_by_magnitude");
static_assert(min_by_magnitude(-1, 2) == -1, "Failed testing min_by_magnitude");
static_assert(min_by_magnitude(2, -1) == -1, "Failed testing min_by_magnitude");
static_assert(min_by_magnitude(1, -2) == 1, "Failed testing min_by_magnitude");
static_assert(min_by_magnitude(-2, 1) == 1, "Failed testing min_by_magnitude");
static_assert(min_by_magnitude(-1, -2) == -1,
              "Failed testing min_by_magnitude");
static_assert(min_by_magnitude(-2, -1) == -1,
              "Failed testing min_by_magnitude");
static_assert(min_by_magnitude({-2, -1, -3}) == -1,
              "Failed testing min_by_magnitude");
static_assert(min_by_magnitude(1, -1) == 1,
              "Failed testing min_by_magnitude");
static_assert(min_by_magnitude(-1, 1) == -1,
              "Failed testing min_by_magnitude");
static_assert(min_by_magnitude({1, -1}) == 1,
              "Failed testing min_by_magnitude");
static_assert(min_by_magnitude({-1, 1}) == -1,
              "Failed testing min_by_magnitude");

// Test string manipulation
constexpr const char *const dummy_string1 = "test 1";
constexpr const char *const dummy_string2 = "test 1";
constexpr const char *const dummy_string3 = "test blah";
static_assert(6 == cstring_length(dummy_string1),
              "Failed testing cstring_length");
static_assert(cstring_hash(dummy_string1) == cstring_hash(dummy_string2),
              "Failed testing cstring_hash");
static_assert(cstring_hash(dummy_string1) != cstring_hash(dummy_string3),
              "Failed testing cstring_hash");

// Test array_equal and replace_at
constexpr std::array<double, 3> array1{{1.2, 3, 4}};
constexpr std::array<double, 3> array1_copy{{1.2, 3, 4}};
static_assert(array_equal(array1, array1_copy), "Failed testing array_equal");
static_assert(not array_equal(array1, std::array<double, 3>{{2.2, 3, 4}}),
              "Failed testing array_equal");
static_assert(array_equal(replace_at<1>(array1, 5.0),
                          std::array<double, 3>{{1.2, 5, 4}}),
              "Failed testing array_equal");

// Test make_array_from_list
static_assert(
    array_equal(std::array<size_t, 3>{{1, 2, 5}},
                make_array_from_list<tmpl::integral_list<size_t, 1, 2, 5>>()),
    "Failed testing make_array_from_list");

// Test as_const
static_assert(cpp17::is_same_v<const double&,
                               decltype(as_const(std::declval<double>()))>,
              "Failed testing as_const");
static_assert(cpp17::is_same_v<const double&,
                               decltype(as_const(std::declval<double&>()))>,
              "Failed testing as_const");
static_assert(5 == as_const(5), "Failed testing as_const");

SPECTRE_TEST_CASE("Unit.Utilities.ConstantExpressions", "[Unit][Utilities]") {
  CHECK((std::array<std::array<size_t, 3>, 3>{
            {std::array<size_t, 3>{{1, 2, 5}}, std::array<size_t, 3>{{8, 7, 2}},
             std::array<size_t, 3>{{3, 9, 0}}}}) ==
        (make_array_from_list<
            tmpl::list<tmpl::integral_list<size_t, 1, 2, 5>,
                       tmpl::integral_list<size_t, 8, 7, 2>,
                       tmpl::integral_list<size_t, 3, 9, 0>>>()));
}
}  // namespace
