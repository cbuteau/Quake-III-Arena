#include <direct.h>

#include "g_main_v8.h"
#include "g_local_v8.h"

#include <v8.h>
#include "..\v8\v8_functions.h"

void get_entity_health(v8::Local<v8::String> property,
	const v8::PropertyCallbackInfo<v8::Value>& info) {
	v8::Local<v8::Object> self = info.Holder();
	v8::Local<v8::External> wrap =
		v8::Local<v8::External>::Cast(self->GetInternalField(0));
	void* ptr = wrap->Value();
	int v = static_cast<gentity_t*>(ptr)->health;
	info.GetReturnValue().Set(v);
}

void set_entity_health(	v8::Local<v8::String> property,
						v8::Local<v8::Value> value,
						const v8::PropertyCallbackInfo<void>& info) {
	v8::Local<v8::Object> self = info.Holder();
	v8::Local<v8::External> wrap =
		v8::Local<v8::External>::Cast(self->GetInternalField(0));
	void* ptr = wrap->Value();
	int v = value->Int32Value(getActiveContext()).ToChecked();
	static_cast<gentity_t*>(ptr)->health = v;
}

v8::Handle<v8::ObjectTemplate> v8_entity_wrapper() {
	//create your function template
	v8::Handle<v8::FunctionTemplate> entity_template = v8::FunctionTemplate::New(getIsolate());

	//get the object's instance template
	v8::Handle<v8::ObjectTemplate> entity_object_template = entity_template->InstanceTemplate();

	//set its internal field count to one for the incoming pointer
	entity_object_template->SetInternalFieldCount(1);

	//add our property accessors
	entity_object_template->SetAccessor(
		v8::String::NewFromUtf8(getIsolate(), "health").ToLocalChecked(), get_entity_health, set_entity_health);

	return entity_object_template;
}

void v8_test_script_function_with_ent(const char* text, const char* func, gentity_t* ent) {
	v8::Handle<v8::ObjectTemplate> wrapper = v8_entity_wrapper();
	v8_test_script_function_with_ptr(text, func, wrapper, ent);
}

void v8_local_init_callbacks() {
}

char BUFFER[64000];

char* v8_load_script_from_file(char* filename) {
	char		cwd[512];
	char		fullpath[512];

	(void)_getcwd(cwd, sizeof(cwd));
	sprintf(fullpath, "%s\\js\\%s", cwd, filename);
	FILE* f = fopen(fullpath, "r");
	if (!f) {
		Com_Printf("file not found: %s\n", fullpath);
		return NULL;
	}
	fseek(f, 0, SEEK_END);
	int sz = ftell(f);
	rewind(f);
	if (sz >= 64000) {
		Com_Printf(BUFFER, "file too large: %s is %i, max allowed is %i", fullpath, sz, 64000);
		fclose(f);
		return NULL;
	}

	size_t len = fread(BUFFER, sizeof(char), sz, f);
	BUFFER[len] = '\0';
	fclose(f);
	return BUFFER;
}