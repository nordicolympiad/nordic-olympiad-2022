#!/usr/bin/env bash

REQUIRE_SAMPLE_REUSE=0
. ../../testdata_tools/gen.sh

use_solution ../empty.py

compile gen_random.py

samplegroup
limits t=0
sample 1
sample 2

gen_all() {
	g=g$1
	tc $g-rand gen_random t=$1 mode=random
	tc $g-dense1 gen_random t=$1 mode=dense
	tc $g-dense2 gen_random t=$1 mode=dense2
	tc $g-dense3 gen_random t=$1 mode=dense3
	tc $g-dense4 gen_random t=$1 mode=dense4
	tc $g-tiny gen_random t=$1 n=3 mode=random
	tc $g-incr gen_random t=$1 mode=incr
	tc $g-decr gen_random t=$1 mode=decr
	tc $g-incrdecr gen_random t=$1 mode=incrdecr
	tc $g-alt gen_random t=$1 mode=alternating
	tc $g-alt2 gen_random t=$1 mode=alternating2
	tc $g-alt3 gen_random t=$1 mode=alternating3
	tc $g-patterns gen_random t=$1 mode=patterns
}

group group1 40
limits t=1
gen_all 1

group group2 40
limits t=2
gen_all 2

group group3 20
limits t=3
gen_all 3
