export function DN_HistogramMode_5(data: number[]): number;
export function DN_HistogramMode_10(data: number[]): number;
export function CO_f1ecac(data: number[]): number;
export function CO_FirstMin_ac(data: number[]): number;
export function CO_HistogramAMI_even_2_5(data: number[]): number;
export function CO_trev_1_num(data: number[]): number;
export function MD_hrv_classic_pnn40(data: number[]): number;
export function SB_BinaryStats_mean_longstretch1(data: number[]): number;
export function SB_TransitionMatrix_3ac_sumdiagcov(data: number[]): number;
export function PD_PeriodicityWang_th0_01(data: number[]): number;
export function CO_Embed2_Dist_tau_d_expfit_meandiff(data: number[]): number;
export function IN_AutoMutualInfoStats_40_gaussian_fmmi(data: number[]): number;
export function FC_LocalSimple_mean1_tauresrat(data: number[]): number;
export function DN_OutlierInclude_p_001_mdrmd(data: number[]): number;
export function DN_OutlierInclude_n_001_mdrmd(data: number[]): number;
export function SP_Summaries_welch_rect_area_5_1(data: number[]): number;
export function SB_BinaryStats_diff_longstretch0(data: number[]): number;
export function SB_MotifThree_quantile_hh(data: number[]): number;
export function SC_FluctAnal_2_rsrangefit_50_1_logi_prop_r1(data: number[]): number;
export function SC_FluctAnal_2_dfa_50_1_2_logi_prop_r1(data: number[]): number;
export function SP_Summaries_welch_rect_centroid(data: number[]): number;
export function FC_LocalSimple_mean3_stderr(data: number[]): number;

export function DN_Mean(data: number[]): number;
export function DN_Spread_Std(data: number[]): number;

type ICatch22 = {
    'DN_HistogramMode_5': number;
    'DN_HistogramMode_10': number;
    'CO_f1ecac': number;
    'CO_FirstMin_ac': number;
    'CO_HistogramAMI_even_2_5': number;
    'CO_trev_1_num': number;
    'MD_hrv_classic_pnn40': number;
    'SB_BinaryStats_mean_longstretch1': number;
    'SB_TransitionMatrix_3ac_sumdiagcov': number;
    'PD_PeriodicityWang_th0_01': number;
    'CO_Embed2_Dist_tau_d_expfit_meandiff': number;
    'IN_AutoMutualInfoStats_40_gaussian_fmmi': number;
    'FC_LocalSimple_mean1_tauresrat': number;
    'DN_OutlierInclude_p_001_mdrmd': number;
    'DN_OutlierInclude_n_001_mdrmd': number;
    'SP_Summaries_welch_rect_area_5_1': number;
    'SB_BinaryStats_diff_longstretch0': number;
    'SB_MotifThree_quantile_hh': number;
    'SC_FluctAnal_2_rsrangefit_50_1_logi_prop_r1': number;
    'SC_FluctAnal_2_dfa_50_1_2_logi_prop_r1': number;
    'SP_Summaries_welch_rect_centroid': number;
    'FC_LocalSimple_mean3_stderr': number;
};
type ICatch24 = ICatch22 & {
    'DN_Mean': number;
    'DN_Spread_Std': number;
}

export function catch22(data: number[]): ICatch22;
export function catch24(data: number[]): ICatch24;
