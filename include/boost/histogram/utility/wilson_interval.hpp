// Copyright 2022 Jay Gohil, Hans Dembinski
//
// Distributed under the Boost Software License, version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_UTILITY_WILSON_INTERVAL_HPP
#define BOOST_HISTOGRAM_UTILITY_WILSON_INTERVAL_HPP

#include <boost/histogram/fwd.hpp>
#include <boost/histogram/utility/binomial_proportion_interval.hpp>
#include <cmath>
#include <utility>

namespace boost {
namespace histogram {
namespace utility {

/**
  Wilson score interval.

  TODO (Hans) explain benefits of this interval here.

  Source:
  https://en.wikipedia.org/wiki/Binomial_proportion_confidence_interval#Wilson_score_interval
*/
template <class ValueType>
class wilson_interval : public binomial_proportion_interval<ValueType> {
  using base_t = binomial_proportion_interval<ValueType>;

public:
  using value_type = typename base_t::value_type;
  using interval_type = typename base_t::interval_type;

  explicit wilson_interval(deviation d = deviation{1.0}) noexcept
      : z_{static_cast<value_type>(d)} {}

  interval_type operator()(value_type successes, value_type failures) const noexcept {
    const value_type half{0.5}, quarter{0.25}, zsq{z_ * z_};
    const value_type s = successes, f = failures;
    const value_type n = s + f;
    const value_type a = (s + half * zsq) / (n + zsq);
    const value_type b = z_ / (n + zsq) * std::sqrt(s * f / n + quarter * zsq);
    return std::make_pair(a - b, a + b);
  }

private:
  value_type z_;
};

} // namespace utility
} // namespace histogram
} // namespace boost

#endif