/**
  ******************************************************************************
  * @file    eightchannel.c
  * @author  AST Embedded Analytics Research Platform
  * @date    2025-11-10T14:39:18+0100
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */


#include "eightchannel.h"
#include "eightchannel_data.h"

#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_eightchannel
 
#undef AI_EIGHTCHANNEL_MODEL_SIGNATURE
#define AI_EIGHTCHANNEL_MODEL_SIGNATURE     "0x37f019137e074479e808a304465a13c1"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "2025-11-10T14:39:18+0100"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_EIGHTCHANNEL_N_BATCHES
#define AI_EIGHTCHANNEL_N_BATCHES         (1)

static ai_ptr g_eightchannel_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_eightchannel_weights_map[1] = AI_C_ARRAY_INIT;



/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  serving_default_keras_tensor_640_output_array, AI_ARRAY_FORMAT_S8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 8, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  gemm_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 16, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  gemm_1_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 8, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  gemm_2_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  nl_3_output_array, AI_ARRAY_FORMAT_S8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 7, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  gemm_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 128, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  gemm_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 16, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  gemm_1_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 128, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  gemm_1_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 8, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  gemm_2_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 56, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  gemm_2_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 7, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  gemm_0_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 88, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  gemm_1_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 56, AI_STATIC)

/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  gemm_2_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 43, AI_STATIC)

/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  nl_3_scratch0_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 124, AI_STATIC)

/**  Array metadata declarations section  *************************************/
/* Int quant #0 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.03786506876349449f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #1 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 16,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.012182489037513733f, 0.010672240518033504f, 0.006963391788303852f, 0.008414410054683685f, 0.006996706128120422f, 0.009930809028446674f, 0.012668767012655735f, 0.012172513641417027f, 0.0063206497579813f, 0.011467568576335907f, 0.009829871356487274f, 0.011655460111796856f, 0.011692119762301445f, 0.013603892177343369f, 0.008877404034137726f, 0.018884431570768356f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #2 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_1_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.04608263075351715f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #3 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_1_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 8,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.008871285244822502f, 0.010513216257095337f, 0.020177679136395454f, 0.007213684264570475f, 0.02142411470413208f, 0.016213344410061836f, 0.017446570098400116f, 0.00914392527192831f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #4 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_2_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.14377491176128387f),
    AI_PACK_INTQ_ZP(62)))

/* Int quant #5 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_2_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 7,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.024365168064832687f, 0.007603948470205069f, 0.013091851025819778f, 0.00781541969627142f, 0.0070578716695308685f, 0.010177450254559517f, 0.010941540822386742f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0)))

/* Int quant #6 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(nl_3_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00390625f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #7 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(serving_default_keras_tensor_640_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.07030853629112244f),
    AI_PACK_INTQ_ZP(-12)))

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  gemm_0_bias, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &gemm_0_bias_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  gemm_0_output, AI_STATIC,
  1, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 1, 1, 16, 16),
  1, &gemm_0_output_array, &gemm_0_output_array_intq)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  gemm_0_scratch0, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 1, 88, 1, 1), AI_STRIDE_INIT(4, 2, 2, 176, 176),
  1, &gemm_0_scratch0_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  gemm_0_weights, AI_STATIC,
  3, 0x1,
  AI_SHAPE_INIT(4, 8, 16, 1, 1), AI_STRIDE_INIT(4, 1, 8, 128, 128),
  1, &gemm_0_weights_array, &gemm_0_weights_array_intq)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  gemm_1_bias, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &gemm_1_bias_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  gemm_1_output, AI_STATIC,
  5, 0x1,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 1, 1, 8, 8),
  1, &gemm_1_output_array, &gemm_1_output_array_intq)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  gemm_1_scratch0, AI_STATIC,
  6, 0x0,
  AI_SHAPE_INIT(4, 1, 56, 1, 1), AI_STRIDE_INIT(4, 2, 2, 112, 112),
  1, &gemm_1_scratch0_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  gemm_1_weights, AI_STATIC,
  7, 0x1,
  AI_SHAPE_INIT(4, 16, 8, 1, 1), AI_STRIDE_INIT(4, 1, 16, 128, 128),
  1, &gemm_1_weights_array, &gemm_1_weights_array_intq)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  gemm_2_bias, AI_STATIC,
  8, 0x0,
  AI_SHAPE_INIT(4, 1, 7, 1, 1), AI_STRIDE_INIT(4, 4, 4, 28, 28),
  1, &gemm_2_bias_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  gemm_2_output, AI_STATIC,
  9, 0x1,
  AI_SHAPE_INIT(4, 1, 7, 1, 1), AI_STRIDE_INIT(4, 1, 1, 7, 7),
  1, &gemm_2_output_array, &gemm_2_output_array_intq)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  gemm_2_scratch0, AI_STATIC,
  10, 0x0,
  AI_SHAPE_INIT(4, 1, 43, 1, 1), AI_STRIDE_INIT(4, 2, 2, 86, 86),
  1, &gemm_2_scratch0_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  gemm_2_weights, AI_STATIC,
  11, 0x1,
  AI_SHAPE_INIT(4, 8, 7, 1, 1), AI_STRIDE_INIT(4, 1, 8, 56, 56),
  1, &gemm_2_weights_array, &gemm_2_weights_array_intq)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  nl_3_output, AI_STATIC,
  12, 0x1,
  AI_SHAPE_INIT(4, 1, 7, 1, 1), AI_STRIDE_INIT(4, 1, 1, 7, 7),
  1, &nl_3_output_array, &nl_3_output_array_intq)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  nl_3_scratch0, AI_STATIC,
  13, 0x0,
  AI_SHAPE_INIT(4, 1, 124, 1, 1), AI_STRIDE_INIT(4, 4, 4, 496, 496),
  1, &nl_3_scratch0_array, NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  serving_default_keras_tensor_640_output, AI_STATIC,
  14, 0x1,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 1, 1, 8, 8),
  1, &serving_default_keras_tensor_640_output_array, &serving_default_keras_tensor_640_output_array_intq)



/**  Layer declarations section  **********************************************/



AI_STATIC_CONST ai_i32 nl_3_nl_params_data[] = { 1235017088, 24, -124 };
AI_ARRAY_OBJ_DECLARE(
    nl_3_nl_params, AI_ARRAY_FORMAT_S32,
    nl_3_nl_params_data, nl_3_nl_params_data, 3, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_3_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_2_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_3_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_3_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  nl_3_layer, 3,
  SM_TYPE, 0x0, NULL,
  sm, forward_sm_integer,
  &nl_3_chain,
  NULL, &nl_3_layer, AI_STATIC, 
  .nl_params = &nl_3_nl_params, 
  .axis = AI_SHAPE_CHANNEL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  gemm_2_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_2_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &gemm_2_weights, &gemm_2_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_2_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  gemm_2_layer, 2,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA_ch,
  &gemm_2_chain,
  NULL, &nl_3_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  gemm_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &gemm_1_weights, &gemm_1_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_1_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  gemm_1_layer, 1,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA_ch,
  &gemm_1_chain,
  NULL, &gemm_2_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  gemm_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &serving_default_keras_tensor_640_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &gemm_0_weights, &gemm_0_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  gemm_0_layer, 0,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA_ch,
  &gemm_0_chain,
  NULL, &gemm_1_layer, AI_STATIC, 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 436, 1, 1),
    436, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 504, 1, 1),
    504, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_EIGHTCHANNEL_IN_NUM, &serving_default_keras_tensor_640_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_EIGHTCHANNEL_OUT_NUM, &nl_3_output),
  &gemm_0_layer, 0x51e520d6, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 436, 1, 1),
      436, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 504, 1, 1),
      504, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_EIGHTCHANNEL_IN_NUM, &serving_default_keras_tensor_640_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_EIGHTCHANNEL_OUT_NUM, &nl_3_output),
  &gemm_0_layer, 0x51e520d6, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool eightchannel_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_eightchannel_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    serving_default_keras_tensor_640_output_array.data = AI_PTR(g_eightchannel_activations_map[0] + 288);
    serving_default_keras_tensor_640_output_array.data_start = AI_PTR(g_eightchannel_activations_map[0] + 288);
    gemm_0_scratch0_array.data = AI_PTR(g_eightchannel_activations_map[0] + 296);
    gemm_0_scratch0_array.data_start = AI_PTR(g_eightchannel_activations_map[0] + 296);
    gemm_0_output_array.data = AI_PTR(g_eightchannel_activations_map[0] + 472);
    gemm_0_output_array.data_start = AI_PTR(g_eightchannel_activations_map[0] + 472);
    gemm_1_scratch0_array.data = AI_PTR(g_eightchannel_activations_map[0] + 288);
    gemm_1_scratch0_array.data_start = AI_PTR(g_eightchannel_activations_map[0] + 288);
    gemm_1_output_array.data = AI_PTR(g_eightchannel_activations_map[0] + 400);
    gemm_1_output_array.data_start = AI_PTR(g_eightchannel_activations_map[0] + 400);
    gemm_2_scratch0_array.data = AI_PTR(g_eightchannel_activations_map[0] + 408);
    gemm_2_scratch0_array.data_start = AI_PTR(g_eightchannel_activations_map[0] + 408);
    gemm_2_output_array.data = AI_PTR(g_eightchannel_activations_map[0] + 496);
    gemm_2_output_array.data_start = AI_PTR(g_eightchannel_activations_map[0] + 496);
    nl_3_scratch0_array.data = AI_PTR(g_eightchannel_activations_map[0] + 0);
    nl_3_scratch0_array.data_start = AI_PTR(g_eightchannel_activations_map[0] + 0);
    nl_3_output_array.data = AI_PTR(g_eightchannel_activations_map[0] + 496);
    nl_3_output_array.data_start = AI_PTR(g_eightchannel_activations_map[0] + 496);
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
  return false;
}




/******************************************************************************/
AI_DECLARE_STATIC
ai_bool eightchannel_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_weights_map(g_eightchannel_weights_map, 1, params)) {
    /* Updating weights (byte) offsets */
    
    gemm_0_weights_array.format |= AI_FMT_FLAG_CONST;
    gemm_0_weights_array.data = AI_PTR(g_eightchannel_weights_map[0] + 0);
    gemm_0_weights_array.data_start = AI_PTR(g_eightchannel_weights_map[0] + 0);
    gemm_0_bias_array.format |= AI_FMT_FLAG_CONST;
    gemm_0_bias_array.data = AI_PTR(g_eightchannel_weights_map[0] + 128);
    gemm_0_bias_array.data_start = AI_PTR(g_eightchannel_weights_map[0] + 128);
    gemm_1_weights_array.format |= AI_FMT_FLAG_CONST;
    gemm_1_weights_array.data = AI_PTR(g_eightchannel_weights_map[0] + 192);
    gemm_1_weights_array.data_start = AI_PTR(g_eightchannel_weights_map[0] + 192);
    gemm_1_bias_array.format |= AI_FMT_FLAG_CONST;
    gemm_1_bias_array.data = AI_PTR(g_eightchannel_weights_map[0] + 320);
    gemm_1_bias_array.data_start = AI_PTR(g_eightchannel_weights_map[0] + 320);
    gemm_2_weights_array.format |= AI_FMT_FLAG_CONST;
    gemm_2_weights_array.data = AI_PTR(g_eightchannel_weights_map[0] + 352);
    gemm_2_weights_array.data_start = AI_PTR(g_eightchannel_weights_map[0] + 352);
    gemm_2_bias_array.format |= AI_FMT_FLAG_CONST;
    gemm_2_bias_array.data = AI_PTR(g_eightchannel_weights_map[0] + 408);
    gemm_2_bias_array.data_start = AI_PTR(g_eightchannel_weights_map[0] + 408);
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/



AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_eightchannel_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_EIGHTCHANNEL_MODEL_NAME,
      .model_signature   = AI_EIGHTCHANNEL_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 448,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x51e520d6,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}



AI_API_ENTRY
ai_bool ai_eightchannel_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_EIGHTCHANNEL_MODEL_NAME,
      .model_signature   = AI_EIGHTCHANNEL_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 448,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x51e520d6,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}


AI_API_ENTRY
ai_error ai_eightchannel_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}


AI_API_ENTRY
ai_error ai_eightchannel_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    AI_CONTEXT_OBJ(&AI_NET_OBJ_INSTANCE),
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}


AI_API_ENTRY
ai_error ai_eightchannel_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[])
{
  ai_error err;
  ai_network_params params;

  err = ai_eightchannel_create(network, AI_EIGHTCHANNEL_DATA_CONFIG);
  if (err.type != AI_ERROR_NONE) {
    return err;
  }
  
  if (ai_eightchannel_data_params_get(&params) != true) {
    err = ai_eightchannel_get_error(*network);
    return err;
  }
#if defined(AI_EIGHTCHANNEL_DATA_ACTIVATIONS_COUNT)
  /* set the addresses of the activations buffers */
  for (ai_u16 idx=0; activations && idx<params.map_activations.size; idx++) {
    AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
  }
#endif
#if defined(AI_EIGHTCHANNEL_DATA_WEIGHTS_COUNT)
  /* set the addresses of the weight buffers */
  for (ai_u16 idx=0; weights && idx<params.map_weights.size; idx++) {
    AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
  }
#endif
  if (ai_eightchannel_init(*network, &params) != true) {
    err = ai_eightchannel_get_error(*network);
  }
  return err;
}


AI_API_ENTRY
ai_buffer* ai_eightchannel_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_inputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_buffer* ai_eightchannel_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_outputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_handle ai_eightchannel_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}


AI_API_ENTRY
ai_bool ai_eightchannel_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = AI_NETWORK_OBJ(ai_platform_network_init(network, params));
  ai_bool ok = true;

  if (!net_ctx) return false;
  ok &= eightchannel_configure_weights(net_ctx, params);
  ok &= eightchannel_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_eightchannel_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}


AI_API_ENTRY
ai_i32 ai_eightchannel_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_EIGHTCHANNEL_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

