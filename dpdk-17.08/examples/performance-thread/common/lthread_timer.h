/*-
 *   BSD LICENSE
 *
 *   Copyright(c) 2015 Intel Corporation. All rights reserved.
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef LTHREAD_TIMER_H_
#define LTHREAD_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "lthread_int.h"
#include "lthread_sched.h"


static inline uint64_t
_ns_to_clks(uint64_t ns)
{
	/*
	 * clkns needs to be divided by 1E9 to get ns clocks. However,
	 * dividing by this first would lose a lot of accuracy.
	 * Dividing after a multiply by ns, could cause overflow of
	 * uint64_t if ns is about 5 seconds [if we assume a max tsc
	 * rate of 4GHz]. Therefore we first divide by 1E4, then
	 * multiply and finally divide by 1E5. This allows ns to be
	 * values many hours long, without overflow, while still keeping
	 * reasonable accuracy.
	 */
	uint64_t clkns = rte_get_tsc_hz() / 1e4;

	clkns *= ns;
	clkns /= 1e5;

	return clkns;
}


static inline void
_timer_start(struct lthread *lt, uint64_t clks)
{
	if (clks > 0) {
		DIAG_EVENT(lt, LT_DIAG_LTHREAD_TMR_START, &lt->tim, clks);
		rte_timer_init(&lt->tim);
		rte_timer_reset(&lt->tim,
				clks,
				SINGLE,
				rte_lcore_id(),
				_sched_timer_cb,
				(void *)lt);
	}
}


static inline void
_timer_stop(struct lthread *lt)
{
	if (lt != NULL) {
		DIAG_EVENT(lt, LT_DIAG_LTHREAD_TMR_DELETE, &lt->tim, 0);
		rte_timer_stop(&lt->tim);
	}
}

#ifdef __cplusplus
}
#endif

#endif /* LTHREAD_TIMER_H_ */
