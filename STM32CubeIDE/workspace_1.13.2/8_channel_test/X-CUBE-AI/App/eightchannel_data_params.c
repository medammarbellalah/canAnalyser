/**
  ******************************************************************************
  * @file    eightchannel_data_params.c
  * @author  AST Embedded Analytics Research Platform
  * @date    2025-11-10T14:39:18+0100
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#include "eightchannel_data_params.h"


/**  Activations Section  ****************************************************/
ai_handle g_eightchannel_activations_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(NULL),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};




/**  Weights Section  ********************************************************/
AI_ALIGNED(32)
const ai_u64 s_eightchannel_weights_array_u64[55] = {
  0xe000001ffff2e81U, 0xfcd8fe0201f4137fU, 0xfe000902fec27ffaU, 0xfd4a7ffaf0ff09ffU,
  0x10f7ff02fd053a81U, 0xe37fd00102fcfafeU, 0xfc11811006f90003U, 0x8110070000010116U,
  0xff080002fbd37ff9U, 0xfa1f8110fc00fdU, 0xfe02ff1881270001U, 0xff00feda7fff0001U,
  0x7fd8050000fdfef5U, 0xfe810ffe020200feU, 0x30101fa2a8113feU, 0xfbfc017ffffe0100U,
  0xffffff78ffffffa1U, 0xffffffbd00000b90U, 0xffffffd9000006e7U, 0xffffff9bffffffeeU,
  0xffffffe6ffffffc9U, 0xffffff47ffffff74U, 0xfffffff8ffffff64U, 0xffffffc1ffffff46U,
  0xf1f0b9727b91e7fU, 0x13ef190cfbfe1762U, 0xd4c1206483ff2f7U, 0xecb2916f1e71a81U,
  0xf901fa02f0fc00U, 0xeaf801fc9b81dc1bU, 0xe646a3f216f8f803U, 0x420fd1cd182a7ffaU,
  0x9906e0fb00fdfb00U, 0x1fff58101030008U, 0xfd06121b0ec7f0d6U, 0xbf81d03edf1117fU,
  0xfdf5ff32f014b981U, 0xff08ffff070bfceeU, 0xd41112ff37d0f4efU, 0xef5331d3647fd938U,
  0xfffffc13000005a9U, 0x16a7000007f0U, 0x7de000006afU, 0x1eaafffffe39U,
  0xca79bd7fbd42eedfU, 0x5b98d8a681f12319U, 0xe58c14c8d97ffc27U, 0x4c7f41f759a83696U,
  0x2a99f46545af81f8U, 0xdddef881ee5356f0U, 0xc67a95810e98571cU, 0xd45000003caU,
  0xffffd5b200001167U, 0xd9cfffffe5eU, 0xe2bU,
};


ai_handle g_eightchannel_weights_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(s_eightchannel_weights_array_u64),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};

