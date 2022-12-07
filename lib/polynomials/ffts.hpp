#pragma once
#include <iostream>
#include <vector>
#include <complex>
// FIXME read other NTTs 
// FIXME try to add modular_int in it
namespace fft
{
    template <typename I>
    I power(I a, I b, const I &mod)
    {
        a = (a) % mod;
        if (a < 0)
            a += mod;
        I p = a;
        a = (I)1;
        while (b > 0)
        {
            if (b & 1)
            {
                a = (a * p) % mod;
            }
            p = (p * p) % mod;
            b >>= 1;
        }
        return a;
    }

    template <typename I>
    I greater_power_of_2(I n)
    {
        I k = 1;
        while (k < n)
        {
            k <<= 1;
        }
        return k;
    }

    // expects input to be of size 2^k
    template <typename T>
    void bit_reversal_permutation(std::vector<T> &a)
    {
        int n = a.size();
        for (int i = 1, j = 0; i < n; i++)
        {
            // i.e. if rev(i) = j
            // then to find rev(i+1) we need to add 1 to reverse of j
            // so for that we find 1st 0 bit in j and convert it to 1
            // and rest 1 bits before that to 0, i.e. same as flipping all leading 1s and next 0
            // adding in reverse bits i.e. adding to msb and carrying to lower bits
            int bit = n >> 1; // note n = 2^k
            for (; j & bit; bit >>= 1)
            {
                // flipping leading 1
                j ^= bit;
            }
            // flipping next 0
            j ^= bit;

            // we only swap once
            if (i < j)
                std::swap(a[i], a[j]);
        }
    }

    template <typename R>
    void fft(std::vector<std::complex<R>> &a, bool inverse = false)
    {
        int n = greater_power_of_2<int>((int)a.size());

        // resize and do bit reversal for inplace fft
        a.resize(n, std::complex<R>((R)0, (R)0));
        fft::bit_reversal_permutation<std::complex<R>>(a);
        R two_R = (R)2.0;
        if (inverse)
        {
            two_R = -two_R;
        }

        for (int len = 2; len <= n; len <<= 1)
        {
            R ang = two_R * std::acos((R)(-1.0)) / len;
            std::complex<R> wlen(std::cos(ang), std::sin(ang));
            for (int i = 0; i < n; i += len)
            {
                std::complex<R> w(1);
                for (int j = 0; j < len / 2; j++)
                {
                    std::complex<R> u = a[i + j], v = a[i + j + len / 2] * w;
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }
        if (inverse)
        {
            for (int i = 0; i < n; i++)
            {
                a[i] /= n;
            }
        }
    }

    // p = c2^k+1, g is primitive root mod p, g^c is 2^k 'th root of unity
    std::vector<long long> PRIMES = {998244353ll, 7340033ll, 97ll};
    std::vector<long long> PRIMITIVE_ROOT = {3ll, 3ll, 3ll};
    std::vector<long long> ROOTS_OF_UNITY = {15311432ll, 2187ll, 28ll};
    std::vector<long long> IROOTS_OF_UNITY = {469870224ll, 4665133ll, 52ll};
    std::vector<long long> TWO_K = {8388608ll, 1048576ll, 32ll};

    template <typename I>
    void add_roots_set(I mod, I g)
    {
        I c = mod - 1;
        I k = 0;
        while (c % 2 == 0)
        {
            c /= 2;
            k++;
        }
        k = (I)(1 << k);
        I w = power<I>((I)g, (I)c, mod);
        I tw = power<I>((I)w, (I)(mod - 2), mod);

        PRIMES.push_back((long long)mod);
        PRIMITIVE_ROOT.push_back((long long)g);
        ROOTS_OF_UNITY.push_back((long long)w);
        IROOTS_OF_UNITY.push_back((long long)tw);
        TWO_K.push_back((long long)k);

        std::cerr << w << ", " << tw << ", " << k << std::endl;
    }

    template <typename I, I mod>
    void ntt(std::vector<I> &a, bool inverse = false)
    {
        I n = greater_power_of_2((I)a.size());
        a.resize(n, 0);

        // resize and do bit reversal for inplace fft
        fft::bit_reversal_permutation(a);

        // find the details about prime in database of primes
        int id = 0;
        for(;id<(int)PRIMES.size();id++)
        {
            if(PRIMES[id]==(long long)mod)
            {
                break;
            }
        }

        I two_k = TWO_K[id];

        // "mod=c*2^k+1 must have large enough order of unit root to apply dft on size n array"
        assert((n<=two_k)&&"mod=c*2^k+1 must have large enough order of unit root to apply dft on size n array"); 

        I w_root;
        if (inverse)
            w_root = IROOTS_OF_UNITY[id];
        else
            w_root = ROOTS_OF_UNITY[id];

        for (I k = 1; k < n; k *= 2)
        {
            // get the root of unity at the level k
            I w_k = w_root;
            for (I i = 2 * k; i < two_k; i <<= 1)
            {
                w_k = (w_k * w_k) % mod;
            }

            for (I i = 0; i < n; i += 2 * k)
            {
                I w_kp = 1;
                for (I j = 0; j < k; ++j)
                {
                    I u = a[i + j];
                    I v = (a[i + j + k] * w_kp) % mod;
                    I x = u + v;
                    if (x >= mod)
                        x -= mod;
                    a[i + j] = x;
                    x = u - v;
                    if (x < 0)
                        x += mod;
                    a[i + j + k] = x;

                    // get the next power of w_k
                    w_kp = (w_k * w_kp) % mod;
                }
            }
        }

        if (inverse)
        {
            I inv_n = power<I>(n, mod - 2, mod);
            for (I i = 0; i < n; i++)
            {
                a[i] = (a[i] * inv_n) % mod;
            }
        }
    }

}