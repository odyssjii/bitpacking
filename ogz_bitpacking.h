/*******************************************************************************
MIT License

Copyright (c) 2021 Omid Ghavami Zeitooni

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/

#if !defined(OGZ_BITPACKING_H)
#define OGZ_BITPACKING_H

#include <inttypes.h>


static inline uint32_t ogz_get_leading_zero_count_u32(uint32_t value)
{
	return (uint32_t)__builtin_clz(value);
}

static inline uint32_t ogz_get_highest_bit_u32(uint32_t value)
{
	return value == 0 ? 0 : 32 - ogz_get_leading_zero_count_u32(value);
}

static inline uint32_t ogz_get_maximum_number_of_bits_u32(const uint32_t *begin, const uint32_t *end)
{
	const uint32_t *p;
	uint32_t acc = 0;

	for (p = begin; p != end; ++p)
		acc |= *p;

	return ogz_get_highest_bit_u32(acc);
}

static inline uint32_t ogz_get_leading_zero_count_u64(uint64_t value)
{
	return (uint32_t)__builtin_clzll(value);
}

static inline uint32_t ogz_get_highest_bit_u64(uint64_t value)
{
	return value == 0 ? 0 : 64 - ogz_get_leading_zero_count_u64(value);
}

static inline uint32_t ogz_get_maximum_number_of_bits_u64(const uint64_t *begin, const uint64_t *end)
{
	const uint64_t *p;
	uint64_t acc = 0;

	for (p = begin; p != end; ++p)
		acc |= *p;

	return ogz_get_highest_bit_u64(acc);
}


void ogz_pack_block_of_32_u32_words(uint32_t *restrict dst, const uint32_t *restrict src, uint32_t bit_count);
void ogz_unpack_block_of_32_u32_words(uint32_t *restrict dst, const uint32_t *restrict src, uint32_t bit_count);

void ogz_pack_block_of_128_u32_words(uint32_t *restrict dst, const uint32_t *restrict src, uint32_t bit_count);
void ogz_unpack_block_of_128_u32_words(uint32_t *restrict dst, const uint32_t *restrict src, uint32_t bit_count);

void ogz_pack_block_of_256_u32_words(uint32_t *restrict dst, const uint32_t *restrict src, uint32_t bit_count);
void ogz_unpack_block_of_256_u32_words(uint32_t *restrict dst, const uint32_t *restrict src, uint32_t bit_count);

void ogz_pack_block_of_64_u64_words(uint64_t *restrict dst, const uint64_t *restrict src, uint32_t bit_count);
void ogz_unpack_block_of_64_u64_words(uint64_t *restrict dst, const uint64_t *restrict src, uint32_t bit_count);

void ogz_pack_block_of_128_u64_words(uint64_t *restrict dst, const uint64_t *restrict src, uint32_t bit_count);
void ogz_unpack_block_of_128_u64_words(uint64_t *restrict dst, const uint64_t *restrict src, uint32_t bit_count);

void ogz_pack_block_of_256_u64_words(uint64_t *restrict dst, const uint64_t *restrict src, uint32_t bit_count);
void ogz_unpack_block_of_256_u64_words(uint64_t *restrict dst, const uint64_t *restrict src, uint32_t bit_count);

#endif
