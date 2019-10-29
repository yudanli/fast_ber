#pragma once

#include "fast_ber/ber_types/GeneralizedTime.hpp"

namespace fast_ber
{
template <typename Identifier = ExplicitIdentifier<UniversalTag::generalized_time>>
using Date = GeneralizedTime<Identifier>;
} // namespace fast_ber
