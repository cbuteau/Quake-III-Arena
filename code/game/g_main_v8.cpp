extern "C"
{
    #include "q_shared.h"
}

#include "g_main_v8.h"

#include <v8.h>
#include "..\v8\v8_functions.h"

// print function implementation - Print to console
void v8_print(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() != 1) {
        args.GetIsolate()->ThrowException(
            v8::String::NewFromUtf8Literal(args.GetIsolate(), "Bad parameters"));
        return;
    }

    v8::Local<v8::Value> a 
        = args[0]->ToString(args.GetIsolate()->GetCurrentContext()).ToLocalChecked();
    v8::String::Utf8Value utf8(args.GetIsolate(), a);
    Com_Printf(*utf8);
}

// plus function implementation - Add two numbers
void v8_plus(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() != 2) {
        args.GetIsolate()->ThrowException(
            v8::String::NewFromUtf8Literal(args.GetIsolate(), "Bad parameters"));
        return;
    }

    uint32_t a = args[0]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
    uint32_t b = args[1]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
    uint32_t c = a + b;

    v8::Local<v8::Integer> ret = v8::Uint32::NewFromUnsigned(args.GetIsolate(), c);
    args.GetReturnValue().Set(ret);
}

void v8_main_init_callbacks() {
    v8_register_callback("qplus", v8_plus);
    v8_register_callback("qprint", v8_print);
}