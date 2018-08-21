/*
 * default_benches.cpp
 *
 * Various "default" benchmarks.
 */

#include "benchmark.hpp"
#include "util.hpp"

extern "C" {
/* misc benches */
bench2_f misc_add_loop32;
bench2_f misc_add_loop64;
bench2_f misc_port7;
bench2_f misc_fusion_add;
bench2_f misc_flag_merge_1;
bench2_f misc_flag_merge_2;
bench2_f misc_flag_merge_3;
bench2_f misc_flag_merge_4;
bench2_f dsb_alignment_cross64;
bench2_f dsb_alignment_nocross64;
bench2_f bmi_tzcnt;
bench2_f bmi_lzcnt;
bench2_f bmi_popcnt;

bench2_f dendibakh_fused;
bench2_f dendibakh_fused_simple;
bench2_f dendibakh_fused_add;
bench2_f dendibakh_fused_add_simple;
bench2_f dendibakh_unfused;
bench2_f fusion_better_fused;
bench2_f fusion_better_unfused;
bench2_f misc_macro_fusion_addjo;

bench2_f adc_0_lat;
bench2_f adc_1_lat;
bench2_f adc_rcx_lat;
bench2_f adc_0_tput;
bench2_f adc_1_tput;
bench2_f adc_rcx_tput;

bench2_f retpoline_dense_call_lfence;
bench2_f retpoline_dense_call_pause;
bench2_f retpoline_sparse_call_base;
bench2_f retpoline_sparse_indep_call_lfence;
bench2_f retpoline_sparse_indep_call_pause;
bench2_f retpoline_sparse_dep_call_lfence;
bench2_f retpoline_sparse_dep_call_pause;
bench2_f indirect_dense_call_pred;
bench2_f indirect_dense_call_unpred;
bench2_f loop_weirdness_fast;

bench2_f tight_loop1;
bench2_f tight_loop2;
bench2_f tight_loop3;

bench2_f dep_add_noloop_128;

bench2_f nehalem_sub1;
bench2_f nehalem_sub2;
bench2_f nehalem_sub3;
bench2_f nehalem_sub4;
bench2_f nehalem_sub5;
bench2_f nehalem_sub6;
bench2_f nehalem_sub7;
bench2_f nehalem_sub8;
bench2_f nehalem_sub9;
bench2_f nehalem_sub10;
bench2_f nehalem_sub11;
bench2_f nehalem_sub12;
bench2_f nehalem_sub13;
bench2_f nehalem_sub14;
bench2_f nehalem_sub15;
bench2_f nehalem_sub16;
bench2_f nehalem_sub17;
bench2_f nehalem_sub18;
bench2_f nehalem_sub19;
bench2_f nehalem_sub20;
bench2_f nehalem_sub21;
bench2_f nehalem_sub22;
bench2_f nehalem_sub23;
bench2_f nehalem_sub24;
bench2_f nehalem_sub25;
bench2_f nehalem_sub26;
bench2_f nehalem_sub27;
bench2_f nehalem_sub28;
bench2_f nehalem_sub29;
bench2_f nehalem_sub30;
bench2_f nehalem_sub31;
bench2_f nehalem_sub32;
bench2_f nehalem_sub33;
bench2_f nehalem_sub34;
bench2_f nehalem_sub35;
bench2_f nehalem_sub36;
bench2_f nehalem_sub37;
bench2_f nehalem_sub38;
bench2_f nehalem_sub39;
bench2_f nehalem_sub40;
bench2_f nehalem_sub41;
bench2_f nehalem_sub42;
bench2_f nehalem_sub43;
bench2_f nehalem_sub44;
bench2_f nehalem_sub45;
bench2_f nehalem_sub46;
bench2_f nehalem_sub47;
bench2_f nehalem_sub48;
bench2_f nehalem_sub49;
bench2_f nehalem_sub50;
bench2_f nehalem_sub51;
bench2_f nehalem_sub52;
bench2_f nehalem_sub53;
bench2_f nehalem_sub54;
bench2_f nehalem_sub55;
bench2_f nehalem_sub56;
bench2_f nehalem_sub57;
bench2_f nehalem_sub58;
bench2_f nehalem_sub59;
bench2_f nehalem_sub60;
bench2_f nehalem_sub61;
bench2_f nehalem_sub62;
bench2_f nehalem_sub63;
bench2_f nehalem_sub64;
bench2_f nehalem_sub65;
bench2_f nehalem_sub66;
bench2_f nehalem_sub67;
bench2_f nehalem_sub68;
bench2_f nehalem_sub69;
bench2_f nehalem_sub70;
bench2_f nehalem_sub71;
bench2_f nehalem_sub72;
bench2_f nehalem_sub73;
bench2_f nehalem_sub74;
bench2_f nehalem_sub75;
bench2_f nehalem_sub76;
bench2_f nehalem_sub77;
bench2_f nehalem_sub78;
bench2_f nehalem_sub79;
bench2_f nehalem_sub80;
bench2_f nehalem_sub81;
bench2_f nehalem_sub82;
bench2_f nehalem_sub83;
bench2_f nehalem_sub84;
bench2_f nehalem_sub85;
bench2_f nehalem_sub86;
bench2_f nehalem_sub87;
bench2_f nehalem_sub88;
bench2_f nehalem_sub89;
bench2_f nehalem_sub90;
bench2_f nehalem_sub91;
bench2_f nehalem_sub92;
bench2_f nehalem_sub93;
bench2_f nehalem_sub94;
bench2_f nehalem_sub95;
bench2_f nehalem_sub96;
bench2_f nehalem_sub97;
bench2_f nehalem_sub98;
bench2_f nehalem_sub99;
bench2_f nehalem_sub100;

}

template <typename TIMER>
void register_misc(GroupList& list) {
    std::shared_ptr<BenchmarkGroup> misc_group = std::make_shared<BenchmarkGroup>("misc", "Miscellaneous tests");

    using default_maker = StaticMaker<TIMER>;

    const uint32_t iters = 10*1000;

    auto maker = DeltaMaker<TIMER>(misc_group.get(), iters);
    auto makerbmi1 = maker.setFeatures({BMI1});

    makerbmi1.template make<misc_add_loop32>("add-32", "32-bit add-loop", 1);
    makerbmi1.template make<misc_add_loop64>("add-64", "64-bit add-loop", 1);

    auto benches = std::vector<Benchmark> {
        default_maker::template make_bench<misc_port7>(misc_group.get(), "port7", "Can port7 be used by loads", 1,
                null_provider, iters),
        default_maker::template make_bench<misc_fusion_add>(misc_group.get(), "fusion-add", "Test micro-fused add", 128,
                null_provider, iters),
        default_maker::template make_bench<misc_macro_fusion_addjo>(misc_group.get(), "add-jo-fusion", "Add-JO fusion", 128,
                null_provider, iters),
        default_maker::template make_bench<adc_0_lat >(misc_group.get(), "adc-0-lat", "adc reg, 0 latency", 128,
                null_provider, iters),
        default_maker::template make_bench<adc_1_lat >(misc_group.get(), "adc-1-lat", "adc reg, 1 latency", 128,
                null_provider, iters),
        default_maker::template make_bench<adc_rcx_lat >(misc_group.get(), "adc-reg-lat", "adc reg,zero-reg latency", 128,
                null_provider, iters),
        default_maker::template make_bench<adc_0_tput>(misc_group.get(), "adc-0-tput", "adc reg, 0 throughput", 128,
                null_provider, iters),
        default_maker::template make_bench<adc_1_tput>(misc_group.get(), "adc-1-tput", "adc reg, 1 throughput", 128,
                null_provider, iters),
        default_maker::template make_bench<adc_rcx_tput>(misc_group.get(), "adc-rcx-tput", "adc reg,zero-reg throughput", 128,
                null_provider, iters),
        default_maker::template make_bench<misc_flag_merge_1>(misc_group.get(), "flag-merge-1", "Flag merge 1", 128,
                null_provider, iters),
        default_maker::template make_bench<misc_flag_merge_2>(misc_group.get(), "flag-merge-2", "Flag merge 2", 128,
                null_provider, iters),
        default_maker::template make_bench<misc_flag_merge_3>(misc_group.get(), "flag-merge-3", "Flag merge 3", 128,
                null_provider, iters),
        default_maker::template make_bench<misc_flag_merge_4>(misc_group.get(), "flag-merge-4", "Flag merge 4", 128,
                null_provider, iters),
        default_maker::template make_bench<tight_loop1>(misc_group.get(), "tight-loop1", "Tight dec loop", 1,
                null_provider, iters * 10),
        default_maker::template make_bench<tight_loop2>(misc_group.get(), "tight-loop2", "Tight dec loop taken jmp", 1,
                null_provider, iters * 10),
        default_maker::template make_bench<tight_loop3>(misc_group.get(), "tight-loop3", "Tight dec loop untaken jmp", 1,
                null_provider, iters * 10),

        // https://news.ycombinator.com/item?id=15935283
        default_maker::template make_bench<loop_weirdness_fast>(misc_group.get(), "loop-weirdness-fast", "Loop weirdness fast", 1,
                []{ return aligned_ptr(1024, 1024); }, 10000),
    };

    misc_group->add(benches);
    list.push_back(misc_group);

    // Tests from https://dendibakh.github.io/blog/2018/02/04/Micro-ops-fusion
    std::shared_ptr<BenchmarkGroup> dendibakh = std::make_shared<BenchmarkGroup>("dendibakh", "Fusion tests from dendibakh blog");

    dendibakh->add(std::vector<Benchmark> {

        // https://dendibakh.github.io/blog/2018/01/18/Code_alignment_issues
        default_maker::template make_bench<dsb_alignment_cross64>(dendibakh.get(), "dsb-align64-cross", "Crosses 64-byte i-boundary", 1,
                []{ return aligned_ptr(1024, 1024); }, 1024),
        default_maker::template make_bench<dsb_alignment_nocross64>(dendibakh.get(), "dsb-align64-nocross", "No cross 64-byte i-boundary", 1,
                []{ return aligned_ptr(1024, 1024); }, 1024),

        default_maker::template make_bench<dendibakh_fused>  (dendibakh.get(),   "fused-original",  "Fused (original)",  1, null_provider, 1024),
        default_maker::template make_bench<dendibakh_fused_simple>  (dendibakh.get(),   "fused-simple",  "Fused (simple addr)", 1, null_provider, 1024),
        default_maker::template make_bench<dendibakh_fused_add>  (dendibakh.get(),"fused-add",  "Fused (add [reg + reg * 4], 1)",  1, null_provider, 1024),
        default_maker::template make_bench<dendibakh_fused_add_simple>  (dendibakh.get(),"fused-add-simple",  "Fused (add [reg], 1)",  1, null_provider, 1024),
        default_maker::template make_bench<dendibakh_unfused>(dendibakh.get(), "unfused-original","Unfused (original)",  1, null_provider, 1024),

        default_maker::template make_bench<fusion_better_fused>(dendibakh.get(), "fusion-better-fused", "Fused summation",  1, []{ return aligned_ptr(64, 8000); }, 1024),
        default_maker::template make_bench<fusion_better_unfused>(dendibakh.get(), "fusion-better-unfused", "Unfused summation",  1, []{ return aligned_ptr(64, 8000); }, 1024)

    });
    list.push_back(dendibakh);

    {
        std::shared_ptr<BenchmarkGroup> bmi_group = std::make_shared<BenchmarkGroup>("bmi", "BMI false-dependency tests");
        list.push_back(bmi_group);
        auto bmi_maker = DeltaMaker<TIMER>(bmi_group.get()).setTags({"default"});

        bmi_maker.template make<bmi_tzcnt>("dep-tzcnt", "dest-dependent tzcnt", 128);
        bmi_maker.template make<bmi_lzcnt>("dep-lzcnt", "dest-dependent lzcnt", 128);
        bmi_maker.template make<bmi_popcnt>("dep-popcnt", "dest-dependent popcnt", 128);
    }

    std::shared_ptr<BenchmarkGroup> retpoline_group = std::make_shared<BenchmarkGroup>("misc/retpoline", "retpoline tests");
    retpoline_group->add(std::vector<Benchmark> {
        default_maker::template make_bench<retpoline_dense_call_pause> (retpoline_group.get(), "retp-call-pause", "Dense retpoline call  pause", 32),
        default_maker::template make_bench<retpoline_dense_call_lfence>(retpoline_group.get(), "retp-call-lfence", "Dense retpoline call lfence", 32),
        default_maker::template make_bench<indirect_dense_call_pred>(retpoline_group.get(),    "ibra-call-pred", "Dense indirect pred calls", 32),
        default_maker::template make_bench<indirect_dense_call_unpred>(retpoline_group.get(),  "ibra-call-unpred", "Dense indirect unpred calls", 32),
        default_maker::template make_bench<retpoline_sparse_indep_call_pause,retpoline_sparse_call_base> (retpoline_group.get(), "retp-sparse-indep-call-pause", "Sparse retpo indep call  pause", 8),
        default_maker::template make_bench<retpoline_sparse_indep_call_lfence,retpoline_sparse_call_base>(retpoline_group.get(), "retp-sparse-indep-call-lfence", "Sparse retpo indep call lfence", 8),
        default_maker::template make_bench<retpoline_sparse_dep_call_pause,retpoline_sparse_call_base> (retpoline_group.get(),   "retp-sparse-dep-call-pause", "Sparse retpo dep call  pause", 8),
        default_maker::template make_bench<retpoline_sparse_dep_call_lfence,retpoline_sparse_call_base>(retpoline_group.get(),   "retp-sparse-dep-call-lfence", "Sparse retpo dep call lfence", 8)
    });
    list.push_back(retpoline_group);

}

#define REG_DEFAULT(CLOCK) template void register_misc<CLOCK>(GroupList& list);

ALL_TIMERS_X(REG_DEFAULT)



