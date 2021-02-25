#pragma once

v8::Isolate* getIsolate();
v8::Local<v8::Context> getActiveContext();

void v8_register_callback(const char* name, v8::FunctionCallback func);

void v8_test_script_function_with_ptr(const char* text, const char* func, v8::Handle<v8::ObjectTemplate>& tmp, void * ent);




