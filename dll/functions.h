#pragma once
#include "nodefaultlib.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
#if !defined(USE_SRP3)
#define ROTL(x,n,w) (((x)<<((n)&(w-1))) | ((x)>>(((-(n))&(w-1)))))
#define ROTL32(x,n) ROTL((x),(n),32)
#define ROTL16(x,n) ROTL((x),(n),16)
#define DLLEXPORT __declspec(dllexport)
	typedef struct {
		uint32_t a, b, c, d, e;
	} bnet_hash_ctx;

	__declspec(dllexport) void w3l_do_hash(char *username, bnet_hash_ctx *ctx);
	__declspec(dllexport) void __fastcall w3l_hash_init(uint32_t *data);


#endif

#ifdef __cplusplus
}
#endif
