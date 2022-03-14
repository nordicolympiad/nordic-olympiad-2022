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
	tc $g-1 gen_random t=$1
}

group group1 40
limits t=1
gen_all 1

group group2 50
limits t=2
gen_all 2

group group3 10
limits t=3
gen_all 3
