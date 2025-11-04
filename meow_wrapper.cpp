#include <cstdint>
#include "meow_hash_x64_aesni.h"

// Garante que o Python (via ctypes) possa encontrar as funções com nomes não embaralhados.
extern "C" {

    // Estrutura de 128 bits para o Python.
    struct MeowU128 {
        uint64_t low;
        uint64_t high;
    };

    // Função de hash principal chamada pelo Python.
    MeowU128 MeowHash_C(void *Seed, uint64_t len, void *data) {
        
        // 1. Chamada à função MeowHash real, que retorna um vetor SIMD (__m128i).
        __m128i hash = MeowHash(Seed, len, data);

        MeowU128 result; 
        
        // 2. Desempacotamento: Transfere os 16 bytes do vetor SIMD para um array simples.
        alignas(16) uint64_t out[2]; 
        _mm_storeu_si128((__m128i*)out, hash); 

        // 3. Montagem do Resultado para o Python.
        result.low = out[0];
        result.high = out[1];
        
        return result;
    }

    // Exporta o ponteiro para o Seed Padrão.
    void* GetMeowDefaultSeed() {
        return (void*)MeowDefaultSeed;
    }
}
