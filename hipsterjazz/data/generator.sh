#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

#ulimit -s unlimited

use_solution js.cpp

compile gen_k_n_m.py
compile gen_k_n.py
compile gen_rand_bip.py
compile gen_rand.py
compile gen_rand_exact.py

MAXN=200

samplegroup
limits maxn=$MAXN
sample_manual 1
sample_manual 2
sample_manual 3

#  $1$    & $10$        &  Every pair of students are friends \\ \hline
group group1 10
tc kn_1 gen_k_n n=1
tc kn_2 gen_k_n n=2
tc 1 # kn_3
tc kn_14 gen_k_n n=14
tc kn_15 gen_k_n n=15
tc kn_20 gen_k_n n=20
tc kn_199 gen_k_n n=199
tc kn_200 gen_k_n n=200

#  $2$    & $15$        &  $N \le 15$ \\ \hline
group group2 15
limits maxn=15
tc 1
tc 2
tc 3
tc rand_7_1 gen_rand n=7 m=10
tc rand_7_2 gen_rand n=7 m=11
tc rand_7_3 gen_rand n=7 m=12
tc rand_7_4 gen_rand n=7 m=13
tc rand_7_5 gen_rand n=7 m=14
tc rand_7_6 gen_rand n=7 m=15
tc knm_7_8 gen_k_n_m n=7 m=8
tc knm_7_8_extra1 gen_k_n_m n=7 m=8 extra=10
tc knm_7_8_extra2 gen_k_n_m n=7 m=8 extra=30
tc knm_1_14 gen_k_n_m n=1 m=14
tc kn_14
tc kn_15
tc rand_15_sparse1 gen_rand n=15 m=30
tc rand_15_sparse2 gen_rand n=15 m=40
tc rand_15_sparse3 gen_rand n=15 m=50
tc rand_15_sparse4 gen_rand n=15 m=60
tc rand_15_dense1 gen_rand n=15 m=70
tc rand_15_dense2 gen_rand n=15 m=80
tc rand_15_dense3 gen_rand n=15 m=90
tc rand_exact_14_4_1 gen_rand_exact n=14 deg=4
tc rand_exact_14_4_2 gen_rand_exact n=14 deg=4
tc rand_exact_14_6_1 gen_rand_exact n=14 deg=6
tc rand_exact_14_6_2 gen_rand_exact n=14 deg=6

#  $3$    & $25$        &  A solution exists where no two friends play the same instrument \\ \hline
group group3 25
limits bipartite=1
tc 3
tc knm_7_8
tc knm_1_14
tc knm_100_100 gen_k_n_m n=100 m=100
tc knm_50_150 gen_k_n_m n=50 m=150
tc knm_14_14 gen_k_n_m n=14 m=14
tc rand_bip_small1 gen_rand_bip n=30 m=30 ed=200
tc rand_bip_small2 gen_rand_bip n=30 m=30 ed=200
tc rand_bip_1 gen_rand_bip n=100 m=100 ed=3000
tc rand_bip_2 gen_rand_bip n=100 m=100 ed=5000
tc rand_bip_3 gen_rand_bip n=100 m=100 ed=7000
tc rand_bip_sparse1 gen_rand_bip n=100 m=100 ed=300
tc rand_bip_sparse2 gen_rand_bip n=100 m=100 ed=300
tc rand_bip_sparse3 gen_rand_bip n=100 m=100 ed=300

#  $4$    & $50$        &  No additional constraints \\ \hline
group group4 50
limits maxn=$MAXN
include_group group1
include_group group2
include_group group3
tc rand_exact_200_50_1 gen_rand_exact n=200 deg=50
tc rand_exact_200_50_2 gen_rand_exact n=200 deg=50
tc rand_exact_200_50_3 gen_rand_exact n=200 deg=50
tc rand_exact_200_50_4 gen_rand_exact n=200 deg=50
tc rand_exact_200_50_5 gen_rand_exact n=200 deg=50
tc rand_exact_200_50_6 gen_rand_exact n=200 deg=50
tc rand_exact_200_50_7 gen_rand_exact n=200 deg=50
tc rand_exact_200_50_8 gen_rand_exact n=200 deg=50
tc knm_100_100_extra1 gen_k_n_m n=100 m=100 extra=500
tc knm_100_100_extra2 gen_k_n_m n=100 m=100 extra=500
tc knm_100_100_extra3 gen_k_n_m n=100 m=100 extra=5000
tc knm_100_100_extra4 gen_k_n_m n=100 m=100 extra=5000
tc knm_100_100_extra5 gen_k_n_m n=100 m=100 extra=5000
tc knm_100_100_extra6 gen_k_n_m n=100 m=100 extra=5000
tc knm_10_10_extra1 gen_k_n_m n=10 m=10 extra=50
tc knm_10_10_extra2 gen_k_n_m n=10 m=10 extra=50
tc knm_10_10_extra3 gen_k_n_m n=10 m=10 extra=50
tc rand_bip_1_extra gen_rand_bip n=100 m=100 ed=3000 extra=1000
tc rand_bip_2_extra gen_rand_bip n=100 m=100 ed=5000 extra=2000
tc rand_bip_3_extra gen_rand_bip n=100 m=100 ed=7000 extra=3000
tc rand_bip_sparse1_extra gen_rand_bip n=100 m=100 ed=300 extra=100
tc rand_bip_sparse2_extra gen_rand_bip n=100 m=100 ed=300 extra=200
tc rand_bip_sparse3_extra gen_rand_bip n=100 m=100 ed=300 extra=300
