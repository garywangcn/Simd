/*
* Simd Library.
*
* Copyright (c) 2011-2013 Yermalayeu Ihar.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy 
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
* copies of the Software, and to permit persons to whom the Software is 
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in 
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#ifndef __SimdMath_h__
#define __SimdMath_h__

#include "Simd/SimdDefs.h"
#include "Simd/SimdConst.h"
#include "Simd/SimdLoad.h"
#include "Simd/SimdStore.h"

namespace Simd
{
    namespace Base
    {
		template <class T> SIMD_INLINE void Swap(T & a, T & b)
		{
			T t = a;
			a = b;
			b = t;
		}

        SIMD_INLINE int Min(int a, int b)
        {
            return a < b ? a : b;
        }

        SIMD_INLINE int Max(int a, int b)
        {
            return a > b ? a : b;
        }

		SIMD_INLINE int RestrictRange(int value, int min = 0, int max = 255)
		{
			return Max(min, Min(max, value));
		}

        SIMD_INLINE int Square(int a)
        {
            return a*a;
        }

        SIMD_INLINE int SquaredDifference(int a, int b)
        {
            return Square(a - b);
        }

		SIMD_INLINE int Average(int a, int b)
		{
			return (a + b + 1) >> 1;
		}

		SIMD_INLINE int Average(int a, int b, int c, int d)
		{
			return (a + b + c + d + 2) >> 2;
		}

		SIMD_INLINE void SortU8(int & a, int & b)
		{
			int d = a - b;
			int m = ~(d >> 8);
			b += d & m;
			a -= d & m;
		}
    }

#ifdef SIMD_SSE2_ENABLE    
	namespace Sse2
	{
		SIMD_INLINE __m128i SaturateI16ToU8(__m128i value)
		{
			return _mm_min_epi16(K16_00FF, _mm_max_epi16(value, K_ZERO));
		}

		SIMD_INLINE __m128i MaxI16(__m128i a, __m128i b, __m128i c)
		{
			return _mm_max_epi16(a, _mm_max_epi16(b, c));
		}

		SIMD_INLINE __m128i MinI16(__m128i a, __m128i b, __m128i c)
		{
			return _mm_min_epi16(a, _mm_min_epi16(b, c));
		}

		SIMD_INLINE void SortU8(__m128i & a, __m128i & b)
		{
			__m128i t = a;
			a = _mm_min_epu8(t, b);
			b = _mm_max_epu8(t, b);
		}

		SIMD_INLINE __m128i ShiftLeft(__m128i a, size_t shift)
		{
			__m128i t = a;
			if(shift & 8)
				t = _mm_slli_si128(t, 8);
			if(shift & 4)
				t = _mm_slli_si128(t, 4);
			if(shift & 2)
				t = _mm_slli_si128(t, 2);
			if(shift & 1)
				t = _mm_slli_si128(t, 1);
			return t;
		}

		SIMD_INLINE __m128i ShiftRight(__m128i a, size_t shift)
		{
			__m128i t = a;
			if(shift & 8)
				t = _mm_srli_si128(t, 8);
			if(shift & 4)
				t = _mm_srli_si128(t, 4);
			if(shift & 2)
				t = _mm_srli_si128(t, 2);
			if(shift & 1)
				t = _mm_srli_si128(t, 1);
			return t;
		}

		SIMD_INLINE __m128i HorizontalSum32(__m128i a)
		{
			return _mm_add_epi64(
				_mm_and_si128(a, K64_00000000FFFFFFFF), 
				_mm_and_si128(_mm_srli_si128(a, 4), K64_00000000FFFFFFFF));
		}
	}
#endif// SIMD_SSE2_ENABLE
}
#endif//__SimdMath_h__