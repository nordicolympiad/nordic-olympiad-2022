#!/usr/bin/env bash

REQUIRE_SAMPLE_REUSE=0
. ../../testdata_tools/gen.sh

use_solution ../empty.py

compile gen_random.py

samplegroup
limits n=-1 nq=-1
sample 1
sample 2

NQ=150
group group1 20
limits nq=$NQ one=1
tc g1-1 gen_random nq=$NQ one=1

NQ=56
group group2 25
limits nq=$NQ
tc g2-1 gen_random nq=$NQ

NQ=35
group group3 30
limits nq=$NQ
tc g3-1 gen_random nq=$NQ

NQ=25
group group4 25
limits nq=$NQ
tc g4-1 gen_random nq=$NQ
