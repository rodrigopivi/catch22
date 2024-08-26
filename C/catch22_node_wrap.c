#include <node_api.h>

// include functions
#include "CO_AutoCorr.h"
#include "DN_HistogramMode_10.h"
#include "DN_HistogramMode_5.h"
#include "DN_Mean.h"
#include "DN_Spread_Std.h"
#include "DN_OutlierInclude.h"
#include "FC_LocalSimple.h"
#include "IN_AutoMutualInfoStats.h"
#include "MD_hrv.h"
#include "PD_PeriodicityWang.h"
#include "SB_BinaryStats.h"
#include "SB_CoarseGrain.h"
#include "SB_MotifThree.h"
#include "SB_TransitionMatrix.h"
#include "SC_FluctAnal.h"
#include "SP_Summaries.h"
#include "butterworth.h"
#include "fft.h"
#include "helper_functions.h"
#include "histcounts.h"
#include "splinefit.h"
#include "stats.h"

// Define the node wrapper function for double return type
napi_value node_wrapper_double(napi_env env, napi_callback_info args, double (*f) (const double*, const int), int normalize) {
    napi_status status;
    napi_value* argv;
    napi_value c_array, result;
    uint32_t array_length;
    size_t argc;
    bool is_arr;
    double* c_array_ptr;
    double result_value;

    // Parse and get arguments
    napi_get_cb_info(env, args, &argc, NULL, NULL, NULL);
    argv = (napi_value*)malloc(argc * sizeof(napi_value));
    status = napi_get_cb_info(env, args, &argc, argv, NULL, NULL);
    if (status != napi_ok) {
        napi_throw_error(env, "0", "Failed napi_get_cb_info");
        free(argv);
        return NULL;
    }
    if (argc != 1) {
        napi_throw_error(env, "0", "Invalid argument count");
        free(argv);
        return NULL;
    }

    // NOTE: hardcoded 'argv[0]' to only map the first argument
    status = napi_is_array(env, argv[0], &is_arr);
    if (status != napi_ok || !is_arr) {
        napi_throw_error(env, "0", "Failed napi_is_array");
        free(argv);
        return NULL;
    }
    status = napi_get_array_length(env, argv[0], &array_length);
    if (status != napi_ok) {
        napi_throw_error(env, "0", "Failed napi_get_array_length");
        free(argv);
        return NULL;
    }

    // Create a Buffer to hold the C array
    status = napi_create_buffer(env, array_length * sizeof(double), (void**)&c_array_ptr, &c_array);
    if (status != napi_ok) {
        napi_throw_error(env, "0", "Failed napi_create_buffer");
        free(argv);
        return NULL;
    }

    // Copy the JavaScript array to the C array
    for (uint32_t i = 0; i < array_length; i++) {
        napi_value element;
        status = napi_get_element(env, argv[0], i, &element);
        if (status != napi_ok) {
            napi_throw_error(env, "0", "Failed napi_get_element");
            free(argv);
            return NULL;
        }
        double e_value;
        status = napi_get_value_double(env, element, &e_value);
        if (status != napi_ok) {
            napi_throw_error(env, "0", "Failed napi_get_value_double");
            free(argv);
            return NULL;
        }
        c_array_ptr[i] = e_value;
    }
    free(argv);

    // Call the C function
    if (normalize){
        double * y_zscored = malloc(array_length * sizeof * y_zscored);
        zscore_norm2(c_array_ptr, array_length, y_zscored);
        result_value = f(y_zscored, array_length);
        free(y_zscored);
    } else {
        result_value = f(c_array_ptr, array_length);
    }

    // Create a JavaScript number to return
    status = napi_create_double(env, result_value, &result);
    if (status != napi_ok) {
        napi_throw_error(env, "0", "Failed napi_create_double");
        return NULL;
    }
    return result;
}

napi_value node_wrapper_int(napi_env env, napi_callback_info args, int (*f) (const double*, const int), int normalize) {
    napi_status status;
    napi_value* argv;
    napi_value c_array, result;
    uint32_t array_length;
    size_t argc;
    bool is_arr;
    double* c_array_ptr;
    int result_value;

    // Parse and get arguments
    napi_get_cb_info(env, args, &argc, NULL, NULL, NULL);
    argv = (napi_value*)malloc(argc * sizeof(napi_value));
    status = napi_get_cb_info(env, args, &argc, argv, NULL, NULL);
    if (status != napi_ok) {
        napi_throw_error(env, "0", "Failed napi_get_cb_info");
        free(argv);
        return NULL;
    }
    if (argc != 1) {
        napi_throw_error(env, "0", "Invalid argument count");
        free(argv);
        return NULL;
    }

    // NOTE: hardcoded 'argv[0]' to only map the first argument
    status = napi_is_array(env, argv[0], &is_arr);
    if (status != napi_ok || !is_arr) {
        napi_throw_error(env, "0", "Failed napi_is_array");
        free(argv);
        return NULL;
    }
    status = napi_get_array_length(env, argv[0], &array_length);
    if (status != napi_ok) {
        napi_throw_error(env, "0", "Failed napi_get_array_length");
        free(argv);
        return NULL;
    }

    // Create a Buffer to hold the C array
    status = napi_create_buffer(env, array_length * sizeof(double), (void**)&c_array_ptr, &c_array);
    if (status != napi_ok) {
        napi_throw_error(env, "0", "Failed napi_create_buffer");
        free(argv);
        return NULL;
    }

    // Copy the JavaScript array to the C array
    for (uint32_t i = 0; i < array_length; i++) {
        napi_value element;
        status = napi_get_element(env, argv[0], i, &element);
        if (status != napi_ok) {
            napi_throw_error(env, "0", "Failed napi_get_element");
            free(argv);
            return NULL;
        }
        double e_value;
        status = napi_get_value_double(env, element, &e_value);
        if (status != napi_ok) {
            napi_throw_error(env, "0", "Failed napi_get_value_double");
            free(argv);
            return NULL;
        }
        c_array_ptr[i] = e_value;
    }
    free(argv);

    // Call the C function
    if (normalize){
        double * y_zscored = malloc(array_length * sizeof * y_zscored);
        zscore_norm2(c_array_ptr, array_length, y_zscored);
        result_value = f(y_zscored, array_length);
        free(y_zscored);
    } else {
        result_value = f(c_array_ptr, array_length);
    }

    // Create a JavaScript number to return
    status = napi_create_int32(env, result_value, &result);
    if (status != napi_ok) {
        napi_throw_error(env, "0", "Failed napi_create_int32");
        return NULL;
    }
    return result;
}

napi_value DN_HistogramMode_5_wrapper(napi_env env, napi_callback_info args) {
    return node_wrapper_double(env, args, &DN_HistogramMode_5, 1);
}

napi_value DN_HistogramMode_10_wrapper(napi_env env, napi_callback_info args) {
    return node_wrapper_double(env, args, &DN_HistogramMode_10, 1);
}

napi_value DN_Mean_wrapper(napi_env env, napi_callback_info args) {
    return node_wrapper_double(env, args, &DN_Mean, 0);
}

napi_value DN_Spread_Std_wrapper(napi_env env, napi_callback_info args) {
    return node_wrapper_double(env, args, &DN_Spread_Std, 0);
}

napi_value CO_f1ecac_wrapper(napi_env env, napi_callback_info args) {
    return node_wrapper_double(env, args, &CO_f1ecac, 1);
}

napi_value CO_FirstMin_ac_wrapper(napi_env env, napi_callback_info args) {
    return node_wrapper_int(env, args, &CO_FirstMin_ac, 1);
}

napi_value CO_HistogramAMI_even_2_5_wrapper(napi_env env, napi_callback_info args) {
    return node_wrapper_double(env, args, &CO_HistogramAMI_even_2_5, 1);
}

napi_value CO_trev_1_num_wrapper(napi_env env, napi_callback_info args) {
    return node_wrapper_double(env, args, &CO_trev_1_num, 1);
}

napi_value MD_hrv_classic_pnn40_wrapper(napi_env env, napi_callback_info args) {
    return node_wrapper_double(env, args, &MD_hrv_classic_pnn40, 1);
}

napi_value SB_BinaryStats_mean_longstretch1_wrapper(napi_env env, napi_callback_info args) {
    return node_wrapper_double(env, args, &SB_BinaryStats_mean_longstretch1, 1);
}

napi_value SB_TransitionMatrix_3ac_sumdiagcov_wrapper(napi_env env, napi_callback_info args) {
    return node_wrapper_double(env, args, &SB_TransitionMatrix_3ac_sumdiagcov, 1);
}

napi_value PD_PeriodicityWang_th0_01_wrapper(napi_env env, napi_callback_info args) {
    return node_wrapper_int(env, args, &PD_PeriodicityWang_th0_01, 1);
}

napi_value CO_Embed2_Dist_tau_d_expfit_meandiff_wrapper(napi_env env, napi_callback_info args) {
    return node_wrapper_double(env, args, &CO_Embed2_Dist_tau_d_expfit_meandiff, 1);
}

napi_value IN_AutoMutualInfoStats_40_gaussian_fmmi_wrapper(napi_env env, napi_callback_info args) {
    return node_wrapper_double(env, args, &IN_AutoMutualInfoStats_40_gaussian_fmmi, 1);
}

napi_value FC_LocalSimple_mean1_tauresrat_wrapper(napi_env env, napi_callback_info args) {
    return node_wrapper_double(env, args, &FC_LocalSimple_mean1_tauresrat, 1);
}

napi_value DN_OutlierInclude_p_001_mdrmd_wrapper(napi_env env, napi_callback_info args) {
    return node_wrapper_double(env, args, &DN_OutlierInclude_p_001_mdrmd, 1);
}

napi_value DN_OutlierInclude_n_001_mdrmd_wrapper(napi_env env, napi_callback_info args) {
    return node_wrapper_double(env, args, &DN_OutlierInclude_n_001_mdrmd, 1);
}

napi_value SP_Summaries_welch_rect_area_5_1_wrapper(napi_env env, napi_callback_info args) {
    return node_wrapper_double(env, args, &SP_Summaries_welch_rect_area_5_1, 1);
}

napi_value SB_BinaryStats_diff_longstretch0_wrapper(napi_env env, napi_callback_info args) {
    return node_wrapper_double(env, args, &SB_BinaryStats_diff_longstretch0, 1);
}

napi_value SB_MotifThree_quantile_hh_wrapper(napi_env env, napi_callback_info args) {
    return node_wrapper_double(env, args, &SB_MotifThree_quantile_hh, 1);
}

napi_value SC_FluctAnal_2_rsrangefit_50_1_logi_prop_r1_wrapper(napi_env env, napi_callback_info args) {
    return node_wrapper_double(env, args, &SC_FluctAnal_2_rsrangefit_50_1_logi_prop_r1, 1);
}

napi_value SC_FluctAnal_2_dfa_50_1_2_logi_prop_r1_wrapper(napi_env env, napi_callback_info args) {
    return node_wrapper_double(env, args, &SC_FluctAnal_2_dfa_50_1_2_logi_prop_r1, 1);
}

napi_value SP_Summaries_welch_rect_centroid_wrapper(napi_env env, napi_callback_info args) {
    return node_wrapper_double(env, args, &SP_Summaries_welch_rect_centroid, 1);
}

napi_value FC_LocalSimple_mean3_stderr_wrapper(napi_env env, napi_callback_info args) {
    return node_wrapper_double(env, args, &FC_LocalSimple_mean3_stderr, 1);
}

// Define the Node.js module
napi_value Init(napi_env env, napi_value exports) {
    napi_status status;
    napi_value DN_HistogramMode_5_fn;
    napi_value DN_HistogramMode_10_fn;
    napi_value DN_Mean_fn;
    napi_value DN_Spread_Std_fn;
    napi_value CO_f1ecac_fn;
    napi_value CO_FirstMin_ac_fn;
    napi_value CO_HistogramAMI_even_2_5_fn;
    napi_value CO_trev_1_num_fn;
    napi_value MD_hrv_classic_pnn40_fn;
    napi_value SB_BinaryStats_mean_longstretch1_fn;
    napi_value SB_TransitionMatrix_3ac_sumdiagcov_fn;
    napi_value PD_PeriodicityWang_th0_01_fn;
    napi_value CO_Embed2_Dist_tau_d_expfit_meandiff_fn;
    napi_value IN_AutoMutualInfoStats_40_gaussian_fmmi_fn;
    napi_value FC_LocalSimple_mean1_tauresrat_fn;
    napi_value DN_OutlierInclude_p_001_mdrmd_fn;
    napi_value DN_OutlierInclude_n_001_mdrmd_fn;
    napi_value SP_Summaries_welch_rect_area_5_1_fn;
    napi_value SB_BinaryStats_diff_longstretch0_fn;
    napi_value SB_MotifThree_quantile_hh_fn;
    napi_value SC_FluctAnal_2_rsrangefit_50_1_logi_prop_r1_fn;
    napi_value SC_FluctAnal_2_dfa_50_1_2_logi_prop_r1_fn;
    napi_value SP_Summaries_welch_rect_centroid_fn;
    napi_value FC_LocalSimple_mean3_stderr_fn;

    // Register the functions with Node.js
    status = napi_create_function(env, "DN_HistogramMode_5", NAPI_AUTO_LENGTH, DN_HistogramMode_5_wrapper, NULL, &DN_HistogramMode_5_fn);
    if (status != napi_ok) {
        return NULL;
    }
    status = napi_set_named_property(env, exports, "DN_HistogramMode_5", DN_HistogramMode_5_fn);
    if (status != napi_ok) {
        return NULL;
    }

    status = napi_create_function(env, "DN_HistogramMode_10", NAPI_AUTO_LENGTH, DN_HistogramMode_10_wrapper, NULL, &DN_HistogramMode_10_fn);
    if (status != napi_ok) {
        return NULL;
    }
    status = napi_set_named_property(env, exports, "DN_HistogramMode_10", DN_HistogramMode_10_fn);
    if (status != napi_ok) {
        return NULL;
    }

    status = napi_create_function(env, "DN_Mean", NAPI_AUTO_LENGTH, DN_Mean_wrapper, NULL, &DN_Mean_fn);
    if (status != napi_ok) {
        napi_throw_error(env, "0", "napi_create_function");
        return NULL;
    }
    status = napi_set_named_property(env, exports, "DN_Mean", DN_Mean_fn);
    if (status != napi_ok) {
        return NULL;
    }

    status = napi_create_function(env, "DN_Spread_Std", NAPI_AUTO_LENGTH, DN_Spread_Std_wrapper, NULL, &DN_Spread_Std_fn);
    if (status != napi_ok) {
        return NULL;
    }
    status = napi_set_named_property(env, exports, "DN_Spread_Std", DN_Spread_Std_fn);
    if (status != napi_ok) {
        return NULL;
    }

    status = napi_create_function(env, "CO_f1ecac", NAPI_AUTO_LENGTH, CO_f1ecac_wrapper, NULL, &CO_f1ecac_fn);
    if (status != napi_ok) {
        return NULL;
    }
    status = napi_set_named_property(env, exports, "CO_f1ecac", CO_f1ecac_fn);
    if (status != napi_ok) {
        return NULL;
    }

    status = napi_create_function(env, "CO_FirstMin_ac", NAPI_AUTO_LENGTH, CO_FirstMin_ac_wrapper, NULL, &CO_FirstMin_ac_fn);
    if (status != napi_ok) {
        return NULL;
    }
    status = napi_set_named_property(env, exports, "CO_FirstMin_ac", CO_FirstMin_ac_fn);
    if (status != napi_ok) {
        return NULL;
    }

    status = napi_create_function(env, "CO_HistogramAMI_even_2_5", NAPI_AUTO_LENGTH, CO_HistogramAMI_even_2_5_wrapper, NULL, &CO_HistogramAMI_even_2_5_fn);
    if (status != napi_ok) {
        return NULL;
    }
    status = napi_set_named_property(env, exports, "CO_HistogramAMI_even_2_5", CO_HistogramAMI_even_2_5_fn);
    if (status != napi_ok) {
        return NULL;
    }

    status = napi_create_function(env, "CO_trev_1_num", NAPI_AUTO_LENGTH, CO_trev_1_num_wrapper, NULL, &CO_trev_1_num_fn);
    if (status != napi_ok) {
        return NULL;
    }
    status = napi_set_named_property(env, exports, "CO_trev_1_num", CO_trev_1_num_fn);
    if (status != napi_ok) {
        return NULL;
    }

    status = napi_create_function(env, "MD_hrv_classic_pnn40", NAPI_AUTO_LENGTH, MD_hrv_classic_pnn40_wrapper, NULL, &MD_hrv_classic_pnn40_fn);
    if (status != napi_ok) {
        return NULL;
    }
    status = napi_set_named_property(env, exports, "MD_hrv_classic_pnn40", MD_hrv_classic_pnn40_fn);
    if (status != napi_ok) {
        return NULL;
    }

    status = napi_create_function(env, "SB_BinaryStats_mean_longstretch1", NAPI_AUTO_LENGTH, SB_BinaryStats_mean_longstretch1_wrapper, NULL, &SB_BinaryStats_mean_longstretch1_fn);
    if (status != napi_ok) {
        return NULL;
    }
    status = napi_set_named_property(env, exports, "SB_BinaryStats_mean_longstretch1", SB_BinaryStats_mean_longstretch1_fn);
    if (status != napi_ok) {
        return NULL;
    }

    status = napi_create_function(env, "SB_TransitionMatrix_3ac_sumdiagcov", NAPI_AUTO_LENGTH, SB_TransitionMatrix_3ac_sumdiagcov_wrapper, NULL, &SB_TransitionMatrix_3ac_sumdiagcov_fn);
    if (status != napi_ok) {
        return NULL;
    }
    status = napi_set_named_property(env, exports, "SB_TransitionMatrix_3ac_sumdiagcov", SB_TransitionMatrix_3ac_sumdiagcov_fn);
    if (status != napi_ok) {
        return NULL;
    }

    status = napi_create_function(env, "PD_PeriodicityWang_th0_01", NAPI_AUTO_LENGTH, PD_PeriodicityWang_th0_01_wrapper, NULL, &PD_PeriodicityWang_th0_01_fn);
    if (status != napi_ok) {
        return NULL;
    }
    status = napi_set_named_property(env, exports, "PD_PeriodicityWang_th0_01", PD_PeriodicityWang_th0_01_fn);
    if (status != napi_ok) {
        return NULL;
    }

    status = napi_create_function(env, "CO_Embed2_Dist_tau_d_expfit_meandiff", NAPI_AUTO_LENGTH, CO_Embed2_Dist_tau_d_expfit_meandiff_wrapper, NULL, &CO_Embed2_Dist_tau_d_expfit_meandiff_fn);
    if (status != napi_ok) {
        return NULL;
    }
    status = napi_set_named_property(env, exports, "CO_Embed2_Dist_tau_d_expfit_meandiff", CO_Embed2_Dist_tau_d_expfit_meandiff_fn);
    if (status != napi_ok) {
        return NULL;
    }

    status = napi_create_function(env, "IN_AutoMutualInfoStats_40_gaussian_fmmi", NAPI_AUTO_LENGTH, IN_AutoMutualInfoStats_40_gaussian_fmmi_wrapper, NULL, &IN_AutoMutualInfoStats_40_gaussian_fmmi_fn);
    if (status != napi_ok) {
        return NULL;
    }
    status = napi_set_named_property(env, exports, "IN_AutoMutualInfoStats_40_gaussian_fmmi", IN_AutoMutualInfoStats_40_gaussian_fmmi_fn);
    if (status != napi_ok) {
        return NULL;
    }

    status = napi_create_function(env, "FC_LocalSimple_mean1_tauresrat", NAPI_AUTO_LENGTH, FC_LocalSimple_mean1_tauresrat_wrapper, NULL, &FC_LocalSimple_mean1_tauresrat_fn);
    if (status != napi_ok) {
        return NULL;
    }
    status = napi_set_named_property(env, exports, "FC_LocalSimple_mean1_tauresrat", FC_LocalSimple_mean1_tauresrat_fn);
    if (status != napi_ok) {
        return NULL;
    }

    status = napi_create_function(env, "DN_OutlierInclude_p_001_mdrmd", NAPI_AUTO_LENGTH, DN_OutlierInclude_p_001_mdrmd_wrapper, NULL, &DN_OutlierInclude_p_001_mdrmd_fn);
    if (status != napi_ok) {
        return NULL;
    }
    status = napi_set_named_property(env, exports, "DN_OutlierInclude_p_001_mdrmd", DN_OutlierInclude_p_001_mdrmd_fn);
    if (status != napi_ok) {
        return NULL;
    }

    status = napi_create_function(env, "DN_OutlierInclude_n_001_mdrmd", NAPI_AUTO_LENGTH, DN_OutlierInclude_n_001_mdrmd_wrapper, NULL, &DN_OutlierInclude_n_001_mdrmd_fn);
    if (status != napi_ok) {
        return NULL;
    }
    status = napi_set_named_property(env, exports, "DN_OutlierInclude_n_001_mdrmd", DN_OutlierInclude_n_001_mdrmd_fn);
    if (status != napi_ok) {
        return NULL;
    }

    status = napi_create_function(env, "SP_Summaries_welch_rect_area_5_1", NAPI_AUTO_LENGTH, SP_Summaries_welch_rect_area_5_1_wrapper, NULL, &SP_Summaries_welch_rect_area_5_1_fn);
    if (status != napi_ok) {
        return NULL;
    }
    status = napi_set_named_property(env, exports, "SP_Summaries_welch_rect_area_5_1", SP_Summaries_welch_rect_area_5_1_fn);
    if (status != napi_ok) {
        return NULL;
    }

    status = napi_create_function(env, "SB_BinaryStats_diff_longstretch0", NAPI_AUTO_LENGTH, SB_BinaryStats_diff_longstretch0_wrapper, NULL, &SB_BinaryStats_diff_longstretch0_fn);
    if (status != napi_ok) {
        return NULL;
    }
    status = napi_set_named_property(env, exports, "SB_BinaryStats_diff_longstretch0", SB_BinaryStats_diff_longstretch0_fn);
    if (status != napi_ok) {
        return NULL;
    }

    status = napi_create_function(env, "SB_MotifThree_quantile_hh", NAPI_AUTO_LENGTH, SB_MotifThree_quantile_hh_wrapper, NULL, &SB_MotifThree_quantile_hh_fn);
    if (status != napi_ok) {
        return NULL;
    }
    status = napi_set_named_property(env, exports, "SB_MotifThree_quantile_hh", SB_MotifThree_quantile_hh_fn);
    if (status != napi_ok) {
        return NULL;
    }

    status = napi_create_function(env, "SC_FluctAnal_2_rsrangefit_50_1_logi_prop_r1", NAPI_AUTO_LENGTH, SC_FluctAnal_2_rsrangefit_50_1_logi_prop_r1_wrapper, NULL, &SC_FluctAnal_2_rsrangefit_50_1_logi_prop_r1_fn);
    if (status != napi_ok) {
        return NULL;
    }
    status = napi_set_named_property(env, exports, "SC_FluctAnal_2_rsrangefit_50_1_logi_prop_r1", SC_FluctAnal_2_rsrangefit_50_1_logi_prop_r1_fn);
    if (status != napi_ok) {
        return NULL;
    }

    status = napi_create_function(env, "SC_FluctAnal_2_dfa_50_1_2_logi_prop_r1", NAPI_AUTO_LENGTH, SC_FluctAnal_2_dfa_50_1_2_logi_prop_r1_wrapper, NULL, &SC_FluctAnal_2_dfa_50_1_2_logi_prop_r1_fn);
    if (status != napi_ok) {
        return NULL;
    }
    status = napi_set_named_property(env, exports, "SC_FluctAnal_2_dfa_50_1_2_logi_prop_r1", SC_FluctAnal_2_dfa_50_1_2_logi_prop_r1_fn);
    if (status != napi_ok) {
        return NULL;
    }

    status = napi_create_function(env, "SP_Summaries_welch_rect_centroid", NAPI_AUTO_LENGTH, SP_Summaries_welch_rect_centroid_wrapper, NULL, &SP_Summaries_welch_rect_centroid_fn);
    if (status != napi_ok) {
        return NULL;
    }
    status = napi_set_named_property(env, exports, "SP_Summaries_welch_rect_centroid", SP_Summaries_welch_rect_centroid_fn);
    if (status != napi_ok) {
        return NULL;
    }

    status = napi_create_function(env, "FC_LocalSimple_mean3_stderr", NAPI_AUTO_LENGTH, FC_LocalSimple_mean3_stderr_wrapper, NULL, &FC_LocalSimple_mean3_stderr_fn);
    if (status != napi_ok) {
        return NULL;
    }
    status = napi_set_named_property(env, exports, "FC_LocalSimple_mean3_stderr", FC_LocalSimple_mean3_stderr_fn);
    if (status != napi_ok) {
        return NULL;
    }
    
    return exports;
}

// Initialize the Node.js module
NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)