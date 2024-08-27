<p align="center"><img src="img/catch22_logo_square.png" alt="catch22 logo" height="220"/></p>

<h1 align="center"><em>catch22</em>: CAnonical Time-series CHaracteristics (for NodeJS)</h1>


A fork of [_catch22_](https://github.com/DynamicsAndNeuralSystems/catch22) to support Nodejs. Just `npm i catch22` and you are ready.

### Example

```ts
const catch22 = require('catch22');

const data = [1,2,3,4,5,6,7,8,9,10];

const features22 = catch22.catch22(data);
const features24 = catch22.catch24(data);

const mode5 = catch22.DN_HistogramMode_5(data);

console.log('features22: ', features22);
console.log('features24: ', features24);
console.log('DN_HistogramMode_5: ', mode5);
```

For more information, check the official [&#x1F4D7;___catch22_ documentation__](https://time-series-features.gitbook.io/catch22/)

### Functions to short names map:

Following the [__feature descriptions__](https://time-series-features.gitbook.io/catch22/information-about-catch22/feature-descriptions):

| Function name                               | Short name         |
|---------------------------------------------|--------------------|
| DN_HistogramMode_5                          | mode_5             |
| DN_HistogramMode_10                         | mode_10            |
| CO_f1ecac                                   | acf_timescale      |
| CO_FirstMin_ac                              | acf_first_min      |
| CO_HistogramAMI_even_2_5                    | ami2               |
| CO_trev_1_num                               | trev               |
| MD_hrv_classic_pnn40                        | high_fluctuation   |
| SB_BinaryStats_mean_longstretch1            | stretch_high       |
| SB_TransitionMatrix_3ac_sumdiagcov          | transition_matrix  |
| PD_PeriodicityWang_th0_01                   | periodicity        |
| CO_Embed2_Dist_tau_d_expfit_meandiff        | embedding_dist     |
| IN_AutoMutualInfoStats_40_gaussian_fmmi     | ami_timescale      |
| FC_LocalSimple_mean1_tauresrat              | whiten_timescale   |
| DN_OutlierInclude_p_001_mdrmd               | outlier_timing_pos |
| DN_OutlierInclude_n_001_mdrmd               | outlier_timing_neg |
| SP_Summaries_welch_rect_area_5_1            | centroid_freq      |
| SB_BinaryStats_diff_longstretch0            | stretch_decreasing |
| SB_MotifThree_quantile_hh                   | entropy_pairs      |
| SC_FluctAnal_2_rsrangefit_50_1_logi_prop_r1 | rs_range           |
| SC_FluctAnal_2_dfa_50_1_2_logi_prop_r1      | dfa                |
| SP_Summaries_welch_rect_centroid            | low_freq_power     |
| FC_LocalSimple_mean3_stderr                 | forecast_error     |
| DN_Mean                                     | mean               |
| DN_Spread_Std                               | SD                 |