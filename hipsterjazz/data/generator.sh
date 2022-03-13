#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

#ulimit -s unlimited

use_solution js.cpp

MAXN=200

samplegroup
limits maxn=$MAXN
sample_manual 1
sample_manual 2
sample_manual 3

#  $1$    & $11$        &  $N \le 15$ \\ \hline
group group1 11
limits maxn=15
tc 1
tc 2
tc 3

#  $2$    & $11$        &  A solution exists where no two friends play the same instrument \\ \hline
group group2 11
limits bipartite=1
tc 3

#  $3$    & $11$        &  No student has more than 3 friends \\ \hline
group group3 11
limits maxdeg=3
tc 1
tc 2
tc 3

#  $4$    & $33$        &  $M \le 200$ \\ \hline
group group4 33
limits maxm=200
include_group group1

# $5$    & $34$        &  No additional constraints \\ \hline
group group5 34
limits maxn=$MAXN
include_group group1
include_group group2
include_group group3
include_group group4
