// SPDX-FileCopyrightText: Copyright 2020 yuzu Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "common/native_clock.h"
#include "common/rdtsc.h"
#include "common/uint128.h"

namespace Common {

NativeClock::NativeClock()
    : rdtsc_frequency{EstimateRDTSCFrequency()},
      ns_rdtsc_factor{GetFixedPoint64Factor(std::nano::den, rdtsc_frequency)},
      us_rdtsc_factor{GetFixedPoint64Factor(std::micro::den, rdtsc_frequency)},
      ms_rdtsc_factor{GetFixedPoint64Factor(std::milli::den, rdtsc_frequency)} {}

u64 NativeClock::GetTimeNS(u64 base_ptc /*= 0*/) const {
    return MultiplyHigh(GetUptime() - base_ptc, ns_rdtsc_factor);
}

u64 NativeClock::GetTimeUS(u64 base_ptc /*= 0*/) const {
    return MultiplyHigh(GetUptime() - base_ptc, us_rdtsc_factor);
}

u64 NativeClock::GetTimeMS(u64 base_ptc /*= 0*/) const {
    return MultiplyHigh(GetUptime() - base_ptc, ms_rdtsc_factor);
}

u64 NativeClock::GetUptime() const {
    return FencedRDTSC();
}

} // namespace Common
