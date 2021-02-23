#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	typedef enum {
		VOID,
		UINT32,
	} v8_arg_t;

	void v8_init();
	void v8_destroy();
	void v8_testplus(void (*print)(const char*));

	void v8_register(const char*, void (*print)(const char*));


#ifdef __cplusplus
}
#endif