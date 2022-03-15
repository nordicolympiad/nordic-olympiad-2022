#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

#ulimit -s unlimited

use_solution nils.cpp

compile gen_random.py
compile gen_subsetsum.py

MAXN=1000

samplegroup
sample_manual 1
sample_manual 2

group group1 8
limits maxn=3 maxm=3 maxc=3
tc tiny-1 gen_random n=1 m=1 maxc=3
tc tiny-2 gen_random n=1 m=1 maxc=3
tc tiny-3 gen_random n=1 m=2 maxc=3
tc tiny-4 gen_random n=3 m=1 maxc=3
tc tiny-5 gen_random n=2 m=2 maxc=3
tc tiny-6 gen_random n=3 m=3 maxc=3
tc tiny-7 gen_random n=3 m=3 maxc=3
tc tiny-8 gen_random n=3 m=3 maxc=3
tc tiny-9 gen_subsetsum n=3 m=3 maxc=3
tc tiny-10 gen_subsetsum n=3 m=3 maxc=3 flipped=1

group group2 5
limits maxn=6 maxm=6 maxc=6
include_group group1
tc small-1 gen_random n=1 m=6 maxc=6
tc small-2 gen_random n=6 m=1 maxc=6
tc small-3 gen_random n=6 m=6 maxc=6
tc small-4 gen_random n=6 m=6 maxc=6
tc small-5 gen_random n=6 m=6 maxc=6
tc small-6 gen_subsetsum n=6 m=6 maxc=6
tc small-7 gen_subsetsum n=6 m=3 maxc=6
tc small-8 gen_subsetsum n=6 m=3 maxc=6 flipped=1
tc small-9 gen_subsetsum n=6 m=6 maxc=6 mode=plusone
tc small-10 gen_subsetsum n=6 m=6 maxc=6 mode=plusone flipped=1
tc small-11 gen_subsetsum n=6 m=4 maxc=6 mode=big
tc small-12 gen_random n=6 m=6 maxc=6 mode=even

group group3 11
limits maxn=1
tc line-1 gen_random n=1 m=1
tc line-2 gen_random n=1 m=10
tc line-3 gen_random n=1 m=$MAXN
tc line-4 gen_random n=1 m=$MAXN
tc line-5 gen_subsetsum n=1 m=$MAXN
tc line-6 gen_subsetsum n=1 m=$MAXN mode=big
tc line-7 gen_subsetsum n=1 m=766 mode=big

group group4 6
limits samec=1
tc same-1 gen_random n=2 m=2 maxc=0 mode=same
tc same-2 gen_random n=2 m=2 maxc=7 mode=same
tc same-3 gen_random n=2 m=4 maxc=7 mode=same
tc same-4 gen_random n=20 m=40 maxc=80 mode=same
tc same-5 gen_random n=20 m=40 maxc=10 mode=same
tc same-6 gen_random n=$MAXN m=$MAXN maxc=$MAXN mode=same
tc same-7 gen_random n=496 m=499 maxc=12 mode=same
tc same-8 gen_random n=499 m=498 maxc=117 mode=same
tc same-9 gen_random n=499 m=499 maxc=0 mode=same
tc same-10 gen_random n=177 m=$MAXN maxc=0 mode=same
tc same-11 gen_random n=997 m=$MAXN maxc=871 mode=same
tc same-12 gen_random n=8 m=3 maxc=7 mode=same
tc same-13 gen_random n=3 m=8 maxc=7 mode=same
tc same-14 gen_random n=$MAXN m=3 maxc=937 mode=same
tc same-15 gen_random n=7 m=$MAXN maxc=937 mode=same
tc same-16 gen_random n=87 m=97 maxc=1000 mode=same
tc 2

group group5 15
limits diffc=1
tc diff-1 gen_random n=2 m=4
tc diff-2 gen_random n=2 m=4
tc diff-3 gen_random n=5 m=6 mode=diff
tc diff-4 gen_random n=4 m=7 mode=diff
tc diff-5 gen_random n=10 m=10 mode=diff
tc diff-6 gen_random n=10 m=10 mode=diff
tc diff-7 gen_random n=10 m=10 mode=diff
tc diff-8 gen_random n=2 m=4 mode=diff2
tc diff-9 gen_random n=10 m=20 mode=diff2
tc diff-10 gen_random n=21 m=42 mode=diff2
tc diff-11 gen_random n=8 m=11 mode=diff
tc diff-12 gen_random n=15 m=5 mode=diff
tc 1

group group6 5
limits maxc=1
tc onezero-1 gen_random n=$MAXN m=$MAXN maxc=1
tc onezero-2 gen_random n=$MAXN m=$MAXN maxc=1 mode=same
tc onezero-3 gen_random n=177 m=$MAXN maxc=1
tc onezero-4 gen_random n=477 m=$MAXN maxc=1
tc onezero-5 gen_random n=$MAXN m=871 maxc=1
tc onezero-6 gen_subsetsum n=$MAXN m=$MAXN maxc=1
tc onezero-7 gen_subsetsum n=$MAXN m=$MAXN maxc=1 flipped=1
tc onezero-8 gen_random n=1 m=1 maxc=1
tc onezero-9 gen_random n=1 m=6 maxc=1
tc onezero-10 gen_random n=999 m=888 maxc=1 mode=same

group group7 15
limits square=1
tc square-1 gen_random n=2 m=2
tc square-2 gen_random n=$MAXN m=$MAXN
tc square-3 gen_random n=$MAXN m=$MAXN
tc square-4 gen_random n=$MAXN m=$MAXN maxc=177 mode=same
tc square-5 gen_subsetsum n=$MAXN m=$MAXN
tc square-6 gen_subsetsum n=$MAXN m=$MAXN maxc=777
tc square-7 gen_subsetsum n=$MAXN m=$MAXN flipped=1
tc square-8 gen_random n=$MAXN m=$MAXN mode=even
tc square-9 gen_random n=$MAXN m=$MAXN mode=even flipped=1
tc square-10 gen_subsetsum n=$MAXN m=$MAXN k=2 mode=twoparts
tc square-11 gen_subsetsum n=$MAXN m=$MAXN k=10 mode=twoparts
tc square-12 gen_subsetsum n=$MAXN m=$MAXN k=300 mode=twoparts
tc square-13 gen_subsetsum n=$MAXN m=$MAXN k=5 mode=twoparts flipped=1
tc square-14 gen_subsetsum n=$MAXN m=$MAXN mode=big
tc square-15 gen_subsetsum n=$MAXN m=$MAXN mode=big flipped=1

group group8 25
limits maxn=100 maxm=100 maxc=100
include_group group2
tc medium-1 gen_random n=100 m=100 maxc=100
tc medium-2 gen_random n=100 m=99 maxc=100
tc medium-3 gen_random n=97 m=99 maxc=100
tc medium-4 gen_random n=100 m=83 maxc=100
tc medium-5 gen_random n=7 m=100 maxc=100
tc medium-6 gen_random n=100 m=100 maxc=77 mode=same
tc medium-7 gen_subsetsum n=100 m=100 maxc=100
tc medium-8 gen_subsetsum n=100 m=99 maxc=100 flipped=1
tc medium-9 gen_subsetsum n=100 m=100 maxc=99 mode=plusone
tc medium-10 gen_subsetsum n=100 m=100 maxc=79 mode=plusone flipped=1
tc medium-11 gen_subsetsum n=80 m=100 maxc=100 mode=big
tc medium-12 gen_subsetsum n=79 m=100 maxc=100 mode=big flipped=1
tc medium-13 gen_random n=100 m=80 maxc=100 mode=even
tc medium-14 gen_random n=100 m=77 maxc=100 mode=even flipped=1
tc medium-15 gen_subsetsum n=100 m=100 maxc=100 k=2 mode=twoparts
tc medium-16 gen_subsetsum n=100 m=100 maxc=100 k=7 mode=twoparts flipped=1
tc medium-17 gen_random n=8 m=3 maxc=97 mode=same

group group9 10
limits maxn=$MAXN
include_group group3
include_group group4
include_group group5
include_group group6
include_group group7
include_group group8
tc large-1 gen_random n=$MAXN m=997 maxc=$MAXN
tc large-2 gen_random n=$MAXN m=944 maxc=$MAXN
tc large-3 gen_random n=$MAXN m=900 maxc=$MAXN
tc large-4 gen_random n=$MAXN m=100 maxc=$MAXN
tc large-5 gen_random n=$MAXN m=2 maxc=$MAXN
tc large-6 gen_random n=201 m=$MAXN maxc=$MAXN
tc large-7 gen_random n=111 m=$MAXN maxc=$MAXN
tc large-8 gen_random n=999 m=$MAXN maxc=$MAXN
tc large-9 gen_subsetsum n=$MAXN m=500
tc large-10 gen_subsetsum n=500 m=$MAXN flipped=1
tc large-11 gen_subsetsum n=$MAXN m=$MAXN mode=plusone
tc large-12 gen_subsetsum n=$MAXN m=$MAXN maxc=757 mode=plusone flipped=1
tc large-13 gen_subsetsum n=777 m=$MAXN mode=big
tc large-14 gen_subsetsum n=177 m=$MAXN mode=big flipped=1
tc large-15 gen_random n=$MAXN m=439 mode=even
tc large-16 gen_random n=$MAXN m=786 mode=even flipped=1