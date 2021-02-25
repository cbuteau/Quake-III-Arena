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

	void v8_test_script(const char* text);
	void v8_test_script_function(const char* text, const char* func);
	void v8_test_script_function_with_arg(const char* text, const char* func, int arg);

#ifdef __cplusplus
}
#endif
