/*
 * Copyright (c) 2024 Centro de Inovacao EDGE
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/drivers/adc.h>
#include <zephyr/kernel.h>

/* ADC node from the devicetree. */
#define ADC_NODE DT_ALIAS(adc1)

/* Data of ADC device specified in devicetree. */
static const struct device *adc = DEVICE_DT_GET(ADC_NODE);

/* Data of ADC channel for IN0. */
static const struct adc_channel_cfg channel_cfg = {
	.channel_id = 0, /* Assuming IN0 is channel 0, adjust if necessary */
	.gain = ADC_GAIN_1,
	.reference = ADC_REF_INTERNAL,
	.differential = 0,
};

/* Get the number of channels defined. */
#define CHANNEL_COUNT 1

int main(void)
{
	int err;
	uint32_t count = 0;
	uint16_t channel_reading[CONFIG_SEQUENCE_SAMPLES];

	/* Options for the sequence sampling. */
	const struct adc_sequence_options options = {
		.extra_samplings = CONFIG_SEQUENCE_SAMPLES - 1,
		.interval_us = 0,
	};

	/* Configure the sampling sequence to be made. */
	struct adc_sequence sequence = {
		.buffer = channel_reading,
		/* buffer size in bytes, not number of samples */
		.buffer_size = sizeof(channel_reading),
		.resolution = CONFIG_SEQUENCE_RESOLUTION,
		.options = &options,
		.channels = BIT(channel_cfg.channel_id), /* Only channel 0 */
	};

	if (!device_is_ready(adc)) {
		printf("ADC controller device %s not ready\n", adc->name);
		return 0;
	}

	/* Configure channel 0 before sampling. */
	err = adc_channel_setup(adc, &channel_cfg);
	if (err < 0) {
		printf("Could not setup channel 0 (%d)\n", err);
		return 0;
	}

#ifndef CONFIG_COVERAGE
	while (1) {
#else
	for (int k = 0; k < 10; k++) {
#endif
		printf("ADC sequence reading [%u]:\n", count++);
		k_msleep(1000);

		err = adc_read(adc, &sequence);
		if (err < 0) {
			printf("Could not read (%d)\n", err);
			continue;
		}

		int32_t val;

		printf("- %s, channel %" PRId32 ", %" PRId32 " sequence samples:\n",
		       adc->name, channel_cfg.channel_id,
		       CONFIG_SEQUENCE_SAMPLES);
		for (size_t sample_index = 0U; sample_index < CONFIG_SEQUENCE_SAMPLES; sample_index++) {
			val = channel_reading[sample_index];

			printf("- - %" PRId32, val);
            printf("\n");
			
		}
	}

	return 0;
}
