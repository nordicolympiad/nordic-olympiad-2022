#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

#ulimit -s unlimited

use_solution nils.cpp

compile gen_random.py

MAXN=1000

samplegroup
sample_manual 1
sample_manual 2
sample_manual 3

group group1 10
limits maxn=3 maxm=3 maxc=3
tc tiny-1 gen_random n=1 m=1 maxc=3
tc tiny-2 gen_random n=1 m=1 maxc=3 mode=valid
tc tiny-3 gen_random n=1 m=2 maxc=3 mode=valid
tc tiny-4 gen_random n=3 m=1 maxc=3 mode=valid
tc tiny-5 gen_random n=2 m=2 maxc=3 mode=valid
tc tiny-6 gen_random n=3 m=3 maxc=3 mode=valid
tc tiny-7 gen_random n=3 m=3 maxc=3 mode=valid changes=1
tc tiny-8 gen_random n=3 m=3 maxc=3

group group2 10
limits maxn=6 maxm=6 maxc=6
include_group group1
tc small-1 gen_random n=1 m=6 maxc=6
tc small-2 gen_random n=6 m=1 maxc=6 mode=valid
tc small-3 gen_random n=6 m=6 maxc=6 mode=valid
tc small-4 gen_random n=6 m=6 maxc=6 mode=valid
tc small-5 gen_random n=6 m=6 maxc=6

group group3 10
limits maxn=1
tc line-1 gen_random n=1 m=1 mode=valid
tc line-2 gen_random n=1 m=10 mode=valid
tc line-3 gen_random n=1 m=$MAXN mode=valid
tc line-4 gen_random n=1 m=$MAXN mode=valid changes=1
tc 3

group group4 10
limits samec=1
tc same-1 gen_random n=2 m=2 maxc=0 mode=same
tc same-2 gen_random n=2 m=2 maxc=7 mode=same
tc same-3 gen_random n=2 m=4 maxc=7 mode=same
tc same-4 gen_random n=20 m=40 maxc=80 mode=same
tc same-5 gen_random n=20 m=40 maxc=10 mode=same
tc same-6 gen_random n=$MAXN m=$MAXN maxc=$MAXN mode=same
tc same-7 gen_random n=499 m=499 maxc=4 mode=same
tc same-8 gen_random n=499 m=498 maxc=117 mode=same
tc same-9 gen_random n=499 m=499 maxc=0 mode=same
tc 2

group group5 10
limits diffc=1
tc diff-1 gen_random n=2 m=4 mode=valid
tc diff-2 gen_random n=2 m=4
tc 1

group group6 10
limits maxc=1
tc onezero-1 gen_random n=$MAXN m=$MAXN maxc=1 mode=valid
tc onezero-2 gen_random n=$MAXN m=$MAXN maxc=1 mode=same
tc onezero-3 gen_random n=177 m=$MAXN maxc=1 mode=valid
tc onezero-4 gen_random n=477 m=$MAXN maxc=1 mode=valid

group group7 10
limits square=1
tc square-1 gen_random n=2 m=2 mode=valid
tc square-2 gen_random n=$MAXN m=$MAXN mode=valid
tc square-3 gen_random n=$MAXN m=$MAXN mode=valid changes=4
tc square-4 gen_random n=$MAXN m=$MAXN maxc=177 mode=same

group group8 10
limits maxn=100 maxm=100 maxc=100
include_group group2
tc medium-1 gen_random n=100 m=100 maxc=100 mode=valid
tc medium-2 gen_random n=100 m=99 maxc=100 mode=valid
tc medium-3 gen_random n=97 m=99 maxc=100 mode=valid
tc medium-4 gen_random n=100 m=83 maxc=100 mode=valid
tc medium-5 gen_random n=7 m=100 maxc=100 mode=valid
tc medium-6 gen_random n=100 m=100 maxc=77 mode=same

group group9 20
limits maxn=$MAXN
include_group group3
include_group group4
include_group group5
include_group group6
include_group group7
include_group group8
tc large-1 gen_random n=$MAXN m=$MAXN maxc=$MAXN mode=valid
tc large-2 gen_random n=$MAXN m=997 maxc=$MAXN mode=valid
tc large-3 gen_random n=$MAXN m=944 maxc=$MAXN mode=valid
tc large-4 gen_random n=$MAXN m=900 maxc=$MAXN mode=valid
tc large-5 gen_random n=$MAXN m=100 maxc=$MAXN mode=valid
tc large-6 gen_random n=$MAXN m=2 maxc=$MAXN mode=valid
tc large-7 gen_random n=201 m=$MAXN maxc=$MAXN mode=valid
tc large-8 gen_random n=111 m=$MAXN maxc=$MAXN mode=valid
tc large-9 gen_random n=999 m=$MAXN maxc=$MAXN mode=valid
