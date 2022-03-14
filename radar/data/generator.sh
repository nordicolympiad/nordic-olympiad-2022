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
	tc $g-rand gen_random t=$1
	tc $g-dense1 gen_random t=$1 mode=dense
	tc $g-dense2 gen_random t=$1 n=40 mode=dense-mid
	tc $g-dense3 gen_random t=$1 n=40 mode=dense-far
	tc $g-dense4 gen_random t=$1 n=5 mode=dense
	tc $g-tiny gen_random t=$1 n=3
	tc $g-incr gen_random t=$1 mode=incr
	tc $g-decr gen_random t=$1 mode=decr
	tc $g-alt gen_random t=$1 mode=alternating
	tc $g-alt2 gen_random t=$1 mode=alternating2
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
