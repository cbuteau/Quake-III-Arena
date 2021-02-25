#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

#include <libplatform/libplatform.h>
#include <v8.h>

#include "v8_init.h"
#include "v8_functions.h"

// v8\v8\out.gn\x64.debug\obj
#pragma comment(lib, "v8_monolith")

// win
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dbghelp.lib")
#pragma comment(lib, "shlwapi.lib")

using namespace v8;

struct V8ContextScope
{
    static V8ContextScope* active;

    v8::Isolate* isolate;
    v8::Local<v8::Context> context;
    v8::Context::Scope context_scope;

    v8::Local<v8::Script> script;

    V8ContextScope(char const* text, v8::Isolate* i, v8::Handle<v8::ObjectTemplate> global) :
        isolate(i),context(v8::Context::New(i, NULL, global)), context_scope(context) {
        active = this;
        v8::Local<v8::String> source =
            v8::String::NewFromUtf8(isolate, text).ToLocalChecked();
        script = v8::Script::Compile(context, source).ToLocalChecked();
    }

    ~V8ContextScope() {
        active = NULL;
    }

    v8::MaybeLocal<v8::Value> Run() {
        v8::TryCatch tryCatch(isolate);
        v8::MaybeLocal<v8::Value> ret = script->Run(context);
        if (ret.IsEmpty()) {
            v8::String::Utf8Value e(isolate, tryCatch.Exception());
            std::cerr << "Exception: " << *e << std::endl;
        }
        else {
            v8::String::Utf8Value r(isolate, ret.ToLocalChecked());
            std::cout << *r << std::endl;
        }
        return ret;
    }

    v8::MaybeLocal<v8::Value> Run(const char* func) {
        v8::MaybeLocal<v8::Value> ret = Run();
        if (!ret.IsEmpty()) {
            v8::MaybeLocal<v8::Value> jsfunc =
                context->Global()->Get(context, v8::String::NewFromUtf8(isolate, func).ToLocalChecked());
            if (!jsfunc.IsEmpty()) {
                v8::MaybeLocal<v8::Object> jsfunc_object = jsfunc.ToLocalChecked()->ToObject(context);
                if (!jsfunc_object.IsEmpty()) {
                    ret = jsfunc_object.ToLocalChecked()->CallAsFunction(context, context->Global(), 0, NULL);
                }
            }
        }
        return ret;
    }

    v8::MaybeLocal<v8::Value> Run(const char* func, int i) {
        v8::MaybeLocal<v8::Value> ret = Run();
        if (!ret.IsEmpty()) {
            v8::MaybeLocal<v8::Value> jsfunc =
                context->Global()->Get(context, v8::String::NewFromUtf8(isolate, func).ToLocalChecked());
            if (!jsfunc.IsEmpty()) {
                v8::MaybeLocal<v8::Object> jsfunc_object = jsfunc.ToLocalChecked()->ToObject(context);
                if (!jsfunc_object.IsEmpty()) {
                    Local<Value> args[] = { v8::Int32::New(isolate, i)};
                    ret = jsfunc_object.ToLocalChecked()->CallAsFunction(context, context->Global(), 1, args);
                }
            }
        }
        return ret;
    }

    v8::MaybeLocal<v8::Value> Run(const char* func, v8::Local<v8::Object> obj) {
        v8::MaybeLocal<v8::Value> ret = Run();
        if (!ret.IsEmpty()) {
            v8::MaybeLocal<v8::Value> jsfunc =
                context->Global()->Get(context, v8::String::NewFromUtf8(isolate, func).ToLocalChecked());
            if (!jsfunc.IsEmpty()) {
                v8::MaybeLocal<v8::Object> jsfunc_object = jsfunc.ToLocalChecked()->ToObject(context);
                if (!jsfunc_object.IsEmpty()) {
                    Local<Value> args[] = { obj };
                    ret = jsfunc_object.ToLocalChecked()->CallAsFunction(context, context->Global(), 1, args);
                }
            }
        }
        return ret;
    }
};

struct V8ScriptScope
{
    v8::Isolate* isolate;

    v8::Isolate::Scope isolate_scope;
    v8::HandleScope handle_scope;

    v8::Handle<v8::ObjectTemplate> global;

    V8ScriptScope(v8::Isolate* i) : 
            isolate(i), isolate_scope(i), 
            handle_scope(i), 
            global(v8::ObjectTemplate::New(i)) {
    }

    v8::MaybeLocal<v8::Value> Run(const char * str) {
        V8ContextScope scope(str, isolate, global);
        return scope.Run();
    }

    v8::MaybeLocal<v8::Value> Run(const char * str, const char * func) {
        V8ContextScope scope(str, isolate, global);
        return scope.Run(func);
    }

    v8::MaybeLocal<v8::Value> Run(const char* str, const char* func, int i) {
        V8ContextScope scope(str, isolate, global);
        return scope.Run(func, i);
    }

    v8::MaybeLocal<v8::Value> Run(const char* str, const char* func, v8::Handle<v8::ObjectTemplate>& tmp, void* ent) {
        V8ContextScope scope(str, isolate, global);

        // wrap the instance
        v8::Local<v8::Object> obj = tmp->NewInstance(getActiveContext()).ToLocalChecked();
        obj->SetInternalField(0, v8::External::New(getIsolate(), ent));

        return scope.Run(func, obj);
    }
};

static std::unique_ptr<Platform> v8_platform;

static v8::Isolate::CreateParams v8_create_params;

static v8::Isolate* v8_isolate;
v8::Isolate* getIsolate() {
    return v8_isolate;
}

V8ContextScope* V8ContextScope::active;
v8::Local<v8::Context> getActiveContext() {
    return V8ContextScope::active->context;
}

static V8ScriptScope* v8_script;

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
    v8_script = new V8ScriptScope(v8_isolate);
};

void v8_destroy() {
    delete v8_script;

    v8_isolate->Dispose();
    delete v8_create_params.array_buffer_allocator;

    // Tear down V8.
    V8::Dispose();
    V8::ShutdownPlatform();
}

// "qprint(' Pew !!! '+qplus(10, 44)+' '+a)};);
void v8_test_script(const char* text) {
    // Run the script to get the result.
    v8::MaybeLocal<v8::Value> result = v8_script->Run(text);
}

// "var qpew = function(){qprint(' Pew !!! '+qplus(10, 44)+' '+a)};","qpew");
void v8_test_script_function(const char* text, const char *func) {
    // Run the script to get the result.
    v8::MaybeLocal<v8::Value> result = v8_script->Run(text, func);
}

// "var qpew = function(a){qprint(' Pew !!! '+qplus(a, 44)+' '+a)};","qpew", 5);
void v8_test_script_function_with_arg(const char* text, const char* func, int i) {
    // Run the script to get the result.
    v8::MaybeLocal<v8::Value> result = v8_script->Run(text, func, i);
}

// "var qpew = function(e){qprint(' Pew !!! '+qplus(e.health, 44)+' '+e.health); if (e.health < 120) e.health = e.health + 10;};"
void v8_test_script_function_with_ptr(const char* text, const char* func, v8::Handle<v8::ObjectTemplate>& tmp, void* ent) {
    // Run the script to get the result.
    v8::MaybeLocal<v8::Value> result = v8_script->Run(text, func, tmp, ent);
}

void v8_register_callback(const char* name, FunctionCallback func) {
    v8_script->global->Set(v8_script->isolate, name,
        v8::FunctionTemplate::New(v8_script->isolate, func));
}