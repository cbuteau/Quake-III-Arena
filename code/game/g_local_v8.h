#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	#include "g_local.h"
	char* v8_load_script_from_file(char* filename);
	void v8_test_script_function_with_ent(const char* text, const char* func, gentity_t *ent);

#ifdef __cplusplus
}
#endif#pragma once
