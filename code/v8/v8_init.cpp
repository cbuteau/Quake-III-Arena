#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

#include <libplatform/libplatform.h>
#include <v8.h>

#include "v8_init.h"

// v8\v8\out.gn\x64.debug\obj
#pragma comment(lib, "v8_monolith")

// win
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dbghelp.lib")
#pragma comment(lib, "shlwapi.lib")

void plus(const v8::FunctionCallbackInfo<v8::Value>& args);

using namespace v8;

static std::unique_ptr<Platform> v8_platform;

static v8::Isolate::CreateParams v8_create_params;
static v8::Isolate* v8_isolate;

struct V8Context
{
    v8::Local<v8::Context> context;
    v8::Context::Scope context_scope;
    V8Context(v8::Isolate* isolate, v8::Handle<v8::ObjectTemplate> global) :
        context(v8::Context::New(isolate, NULL, global)), context_scope(context) {}
};

struct V8Scopes
{
    v8::Isolate* isolate;
    v8::Isolate::Scope isolate_scope;
    v8::HandleScope handle_scope;
    v8::Handle<v8::ObjectTemplate> global;

    V8Context * context;
    v8::Local<v8::Script> script;

    V8Scopes(v8::Isolate* i) : isolate(i), isolate_scope(i), handle_scope(i) {
        // setup functions.
        global = v8::ObjectTemplate::New(i);
        global->Set(i, "plus", v8::FunctionTemplate::New(i, plus));

        // define a context
        context = new V8Context(i, global);
    }

    void setScript(char const *str) {
        // manage javascript
        v8::Local<v8::String> source = 
            v8::String::NewFromUtf8(isolate, str).ToLocalChecked();
        script = v8::Script::Compile(context->context, source).ToLocalChecked();
    }
};

static V8Scopes* v8_scopes;

struct V8Func
{
    void (*target)(const char*);
    Local<FunctionTemplate> callback;
    FunctionCallback* hook;

    V8Func(const char* name, void (*func)(const char*)) {
        target = func;
        callback = v8::FunctionTemplate::New(v8_scopes->isolate, *hook);
        v8_scopes->global->Set(v8_scopes->isolate,
            "plus", v8::FunctionTemplate::New(v8_scopes->isolate, plus));
    }

    void call(const v8::FunctionCallbackInfo<v8::Value>& args) {
    }
};

void v8_init() {
    char			cwd[256];
    static char		argv0[256];
    char* c = _getcwd(cwd, sizeof(cwd));
    sprintf(argv0, "%s\\quake3.exe", cwd);

    // Initialize V8.
    V8::InitializeICUDefaultLocation(argv0);
    V8::InitializeExternalStartupData(argv0);

    v8_platform = platform::NewDefaultPlatform();
    V8::InitializePlatform(v8_platform.get());
    V8::Initialize();

    // Create a new Isolate and make it the current one.
    v8_create_params.array_buffer_allocator =
        v8::ArrayBuffer::Allocator::NewDefaultAllocator();

    // THIS TAKES NOTICABLE TIME
    v8_isolate = v8::Isolate::New(v8_create_params);
    v8_scopes = new V8Scopes(v8_isolate);
    v8_scopes->setScript("plus(120,44);");  
};

void v8_destroy() {
    delete v8_scopes;

    v8_isolate->Dispose();
    delete v8_create_params.array_buffer_allocator;

    // Tear down V8.
    V8::Dispose();
    V8::ShutdownPlatform();
}

void v8_register(const char* name, void (*func)(const char*)) {
    v8_scopes->global->Set(v8_scopes->isolate, name, 
        v8::FunctionTemplate::New(v8_scopes->isolate, plus));
}

void v8_testplus(void (*print)(const char *)) {
    // Run the script to get the result.
    v8::Local<v8::Value> result = 
        v8_scopes->script->Run(v8_scopes->context->context).ToLocalChecked();
    // Convert the result to an UTF8 string and print it.
    v8::String::Utf8Value utf8(v8_isolate, result);
    print(*utf8);
    print(" pew!!! ");
}

// plus function implementation - Add two numbers
void plus(const v8::FunctionCallbackInfo<v8::Value>& args)
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