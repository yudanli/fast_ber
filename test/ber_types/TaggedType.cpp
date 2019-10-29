#include "fast_ber/ber_types/TaggedType.hpp"
#include "fast_ber/ber_types/All.hpp"
#include "fast_ber/ber_types/Identifier.hpp"
#include "fast_ber/ber_types/Integer.hpp"

#include <catch2/catch.hpp>

#include <array>

TEST_CASE("TaggedType: Assign")
{
    using Tag       = fast_ber::ImplicitIdentifier<fast_ber::Class::universal, fast_ber::Tag(5)>;
    using TaggedInt = fast_ber::TaggedType<fast_ber::Integer<>, Tag>;

    fast_ber::Integer<> a(4);
    TaggedInt           b = a;

    REQUIRE(b == 4);
    REQUIRE(fast_ber::val(identifier(&b).tag()) == 5);

    static_assert(std::is_same<decltype(fast_ber::identifier(static_cast<TaggedInt*>(nullptr))), Tag>::value,
                  "Double Tagged Identifier");
}

TEST_CASE("TaggedType: Double Tagged")
{
    using TestInnerTag    = fast_ber::ImplicitIdentifier<fast_ber::Class::universal, fast_ber::Tag(5)>;
    using TestOuterTag    = fast_ber::ImplicitIdentifier<fast_ber::Class::universal, fast_ber::Tag(10)>;
    using DoubleTaggedInt = fast_ber::TaggedType<fast_ber::TaggedType<fast_ber::Integer<>, TestInnerTag>, TestOuterTag>;

    fast_ber::Integer<> a(4);
    DoubleTaggedInt     b = a;

    REQUIRE(b == 4);
    REQUIRE(fast_ber::val(identifier(&b).tag()) == 10);

    static_assert(
        std::is_same<decltype(fast_ber::identifier(static_cast<DoubleTaggedInt*>(nullptr))), TestOuterTag>::value,
        "Double Tagged Identifier");
}

TEST_CASE("TaggedType: Double Tagged Explicit")
{
    using TestInnerTag =
        fast_ber::TaggedExplicitIdentifier<fast_ber::Class::application, fast_ber::Tag(5),
                                           fast_ber::ExplicitIdentifier<fast_ber::UniversalTag::integer>>;
    using TestOuterTag = fast_ber::ImplicitIdentifier<fast_ber::Class::context_specific, fast_ber::Tag(10)>;
    using ExplicitTag  = fast_ber::ExplicitIdentifier<fast_ber::UniversalTag::integer>;

    using DoubleTaggedInt =
        fast_ber::TaggedType<fast_ber::TaggedType<fast_ber::Integer<ExplicitTag>, TestInnerTag>, TestOuterTag>;

    static_assert(
        std::is_same<decltype(fast_ber::identifier(static_cast<DoubleTaggedInt*>(nullptr))), TestOuterTag>::value,
        "Double Tagged Identifier");
}

TEST_CASE("TaggedType: Encode Decode")
{
    fast_ber::TaggedType<fast_ber::Integer<>,
                         fast_ber::ImplicitIdentifier<fast_ber::Class::universal, fast_ber::Tag(5)>>
        a = 10;
    fast_ber::TaggedType<fast_ber::Integer<>,
                         fast_ber::ImplicitIdentifier<fast_ber::Class::universal, fast_ber::Tag(5)>>
                             b      = 20;
    std::array<uint8_t, 100> buffer = {};

    fast_ber::encode(absl::Span<uint8_t>(buffer), a);
    fast_ber::decode(absl::Span<const uint8_t>(buffer), b);

    REQUIRE(b == 10);
}

TEST_CASE("TaggedType: Tagged Enum")
{
    enum class TestEnum
    {
        option_one,
        option_two,
        option_three
    };

    static_assert(
        std::is_same<decltype(fast_ber::identifier(
                         static_cast<fast_ber::TaggedType<
                             TestEnum, fast_ber::ExplicitIdentifier<fast_ber::UniversalTag::octet_string>>*>(nullptr))),
                     fast_ber::ExplicitIdentifier<fast_ber::UniversalTag::octet_string>>::value,
        "Tagged Enum Identifier");
}
