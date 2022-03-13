#!/usr/bin/env bash

REQUIRE_SAMPLE_REUSE=0
. ../../testdata_tools/gen.sh

use_solution ../empty.py

compile gen_random.py

samplegroup
limits n=-1 nq=-1
sample 1
sample 2

SCORE=20
NQ=150
group group1 $SCORE
limits nq=$NQ
tc g1-1 gen_random nq=$NQ score=$SCORE

SCORE=20
NQ=56
group group2 $SCORE
limits nq=$NQ
tc g2-1 gen_random nq=$NQ score=$SCORE

SCORE=35
NQ=35
group group3 $SCORE
limits nq=$NQ
tc g3-1 gen_random nq=$NQ score=$SCORE

SCORE=25
NQ=25
group group4 $SCORE
limits nq=$NQ
tc g4-1 gen_random nq=$NQ score=$SCORE
