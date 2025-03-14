// Copyright (C) 2025 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
#include <stdio.h>
#include <stdlib.h>

#include "openvino/genai/c/llm_pipeline.h"

#define CHECK_STATUS(return_status)                                                      \
    if (return_status != OK) {                                                           \
        fprintf(stderr, "[ERROR] return status %d, line %d\n", return_status, __LINE__); \
        goto err;                                                                        \
    }

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <MODEL_DIR> \"<PROMPT>\"\n", argv[0]);
        return EXIT_FAILURE;
    }
    const char* model_dir = argv[1];
    const char* prompt = argv[2];

    ov_genai_llm_pipeline* pipeline = NULL;
    ov_genai_generation_config* config = NULL;
    const char* device = "CPU";  // GPU, NPU can be used as well
    char output[1024];

    CHECK_STATUS(ov_genai_llm_pipeline_create(model_dir, device, &pipeline));
    CHECK_STATUS(ov_genai_generation_config_create(&config));
    CHECK_STATUS(ov_genai_generation_config_set_max_new_tokens(config, 100));

    CHECK_STATUS(ov_genai_llm_pipeline_generate(pipeline, prompt, config, NULL, output, sizeof(output)));

    printf("%s\n", output);

err:
    if (pipeline)
        ov_genai_llm_pipeline_free(pipeline);
    if (config)
        ov_genai_generation_config_free(config);

    return EXIT_SUCCESS;
}
