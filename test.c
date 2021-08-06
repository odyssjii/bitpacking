#include "ogz_bitpacking.c"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

static uint64_t
gen_random_number(uint32_t bit_count)
{
	uint64_t result = 0;
	if (bit_count == 0)
		return result;

	uint32_t shift = bit_count - 1;

	result |= (1LLU << shift);
	for (uint32_t i = 0; i < shift; ++i)
		if (rand() > (RAND_MAX / 2))
			result |= (1LLU << i);

	return result;
}

static void
gen_random_numbers_u32(uint32_t *out, uint32_t count, uint32_t bit_count)
{
	for (uint32_t i = 0; i < count; ++i)
		out[i] = (uint32_t)gen_random_number(bit_count);
}

static void
gen_random_numbers_u64(uint64_t *out, uint32_t count, uint32_t bit_count)
{
	for (uint32_t i = 0; i < count; ++i)
		out[i] = gen_random_number(bit_count);
}

static bool
packing_test_u32(void (*pack)(uint32_t *restrict dst, const uint32_t *restrict src, uint32_t bit_count),
		 void (*unpack)(uint32_t *restrict dst, const uint32_t *restrict src, uint32_t bit_count),
		 uint32_t count)
{
	uint32_t *source = malloc(sizeof(uint32_t) * count);
	uint32_t *packed = malloc(sizeof(uint32_t) * count);
	uint32_t *unpacked = malloc(sizeof(uint32_t) * count);

	for (uint32_t run = 0; run < 1000; ++run) {
		for (uint32_t bit_count = 0; bit_count <= 32; ++bit_count) {
			gen_random_numbers_u32(source, count, bit_count);

			pack(packed, source, bit_count);
			unpack(unpacked, packed, bit_count);

			for (uint32_t i = 0; i < count; ++i)
				if (source[i] != unpacked[i])
					return false;
		}
	}

	return true;
}

static bool
packing_test_u64(void (*pack)(uint64_t *restrict dst, const uint64_t *restrict src, uint32_t bit_count),
		 void (*unpack)(uint64_t *restrict dst, const uint64_t *restrict src, uint32_t bit_count),
		 uint32_t count)
{
	uint64_t *source = malloc(sizeof(uint64_t) * count);
	uint64_t *packed = malloc(sizeof(uint64_t) * count);
	uint64_t *unpacked = malloc(sizeof(uint64_t) * count);

	for (uint32_t run = 0; run < 1000; ++run) {
		for (uint32_t bit_count = 0; bit_count <= 64; ++bit_count) {
			gen_random_numbers_u64(source, count, bit_count);

			pack(packed, source, bit_count);
			unpack(unpacked, packed, bit_count);

			for (uint32_t i = 0; i < count; ++i) {
				if (source[i] != unpacked[i]) {
					fprintf(stderr, "Failed on bit count: %u\n. Expected: %"PRIu64", Actual: %"PRIu64"\n", bit_count, source[i], unpacked[i]);
					return false;
				}
			}
		}
	}

	return true;
}

int main()
{
	fprintf(stderr, "Running tests...\n");

	fprintf(stderr, "BLOCK OF 32 U32 WORDS...");
	if (packing_test_u32(ogz_pack_block_of_32_u32_words, ogz_unpack_block_of_32_u32_words, 32))
		fprintf(stderr, "OK\n");

	fprintf(stderr, "BLOCK OF 128 U32 WORDS...");
	if (packing_test_u32(ogz_pack_block_of_128_u32_words, ogz_unpack_block_of_128_u32_words, 128))
		fprintf(stderr, "OK\n");

	fprintf(stderr, "BLOCK OF 256 U32 WORDS...");
	if (packing_test_u32(ogz_pack_block_of_256_u32_words, ogz_unpack_block_of_256_u32_words, 256))
		fprintf(stderr, "OK\n");

	fprintf(stderr, "BLOCK OF 64 U64 WORDS...");
	if (packing_test_u64(ogz_pack_block_of_64_u64_words, ogz_unpack_block_of_64_u64_words, 64))
		fprintf(stderr, "OK\n");

	fprintf(stderr, "BLOCK OF 128 U64 WORDS...");
	if (packing_test_u64(ogz_pack_block_of_128_u64_words, ogz_unpack_block_of_128_u64_words, 128))
		fprintf(stderr, "OK\n");

	fprintf(stderr, "BLOCK OF 256 U64 WORDS...");
	if (packing_test_u64(ogz_pack_block_of_256_u64_words, ogz_unpack_block_of_256_u64_words, 256))
		fprintf(stderr, "OK\n");

	fprintf(stderr, "\n");
	return 0;
}
