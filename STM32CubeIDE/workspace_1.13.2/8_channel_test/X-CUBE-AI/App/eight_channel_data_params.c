/**
  ******************************************************************************
  * @file    eight_channel_data_params.c
  * @author  AST Embedded Analytics Research Platform
  * @date    2025-11-10T14:38:56+0100
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

#include "eight_channel_data_params.h"


/**  Activations Section  ****************************************************/
ai_handle g_eight_channel_activations_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(NULL),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};




/**  Weights Section  ********************************************************/
AI_ALIGNED(32)
const ai_u64 s_eight_channel_weights_array_u64[58] = {
  0x2fdfe08d37ff401U, 0xf6fffe05fafbf5ffU, 0xff01000004f8027fU, 0x8107000bfd7f0200U,
  0xfcff120000fcf71dU, 0xb67fed010a7f0afdU, 0x2b8100fff7fa0208U, 0x3030c0a11fe07e8U,
  0x20f8132fc010306U, 0x813501fd04fefe0fU, 0x6810f060000fa01U, 0xff01ff0101ff01ffU,
  0x7ffd080ffc810100U, 0x81fe0502fff9f910U, 0xd9030201fffd0043U, 0x1c810000fdfef77fU,
  0xfd01110900ffff02U, 0x101f70104030a81U, 0xffffffe2ffffff3fU, 0x28fffffa31U,
  0x10ffffffdbU, 0x7000008f2U, 0xfffffff000000031U, 0x2efffffcf6U,
  0x190000000aU, 0xffffffff00000014U, 0xfd0102fc810000U, 0xff06ff00019d00fdU,
  0xfe2229f28101fa0aU, 0x14deb7aaad00c502U, 0xf122061a02fb830bU, 0x1fd70f08faf90581U,
  0xd878f1f07583012aU, 0x1b810a0e61a62edeU, 0x7f2cf27bd8b20812U, 0x17d80e13d3c86622U,
  0x2819042c057fff11U, 0x1ce20c0cf8572407U, 0xd75ad00061b06f7U, 0xbc81fc0504163205U,
  0x19dff90d00f21483U, 0xf91b818b4afb1e1aU, 0x5bc00000892U, 0x11e7000003c5U,
  0xfffffc6b00000f16U, 0xe32fffff9d8U, 0xc4a8b9c2d081bac7U, 0xf27ffea5b84e43f8U,
  0xd9f37d0081cae53aU, 0x7fa774e2d7bb4218U, 0xed397fd22b10a547U, 0xe9af7f95e843a538U,
  0x7f1277dddf9be339U, 0xfffcf30d0afbfd81U, 0x696fffffe5aU, 0xfffffc6e0000016dU,
  0x677ffffee69U, 0x88fffff940U,
};


ai_handle g_eight_channel_weights_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(s_eight_channel_weights_array_u64),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};

