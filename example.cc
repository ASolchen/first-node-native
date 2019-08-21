#include <node.h>
#include <stdio.h>
#include <stdlib.h>

const int maxValue = 10;
int numberOfCalls = 0;

void WhoAmI(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();
  auto message = v8::String::NewFromUtf8(isolate, "I'm a Node Hero!");
  args.GetReturnValue().Set(message);
}

void myArray(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();
   FILE *fp; 
   fp = fopen("C:\\Users\\asolchenberger\\Documents\\repo\\rdd_viewer\\GOV_Speed_pc.rdd", "rb"); // read bin mode
  auto message = v8::Array::New(isolate,100);
  double val;
  long b=0;
  fseek(fp, 1024, SEEK_CUR);
  for(int i=0; i<100; i+=2){
    fread(&val, sizeof(val), 1, fp);
    message->Set(i, v8::Number::New(isolate, val));
    fread(&val, sizeof(val), 1, fp);
    message->Set(i+1, v8::Number::New(isolate, val));
  }
  fclose(fp);
  args.GetReturnValue().Set(message);
}


void Increment(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();

  if (!args[0]->IsNumber()) {
    isolate->ThrowException(v8::Exception::TypeError(
          v8::String::NewFromUtf8(isolate, "Argument must be a number")));
    return;
  }

  double argsValue = args[0]->NumberValue();
  if (numberOfCalls + argsValue > maxValue) {
    isolate->ThrowException(v8::Exception::Error(
          v8::String::NewFromUtf8(isolate, "Counter went through the roof!")));
    return;
  }

  numberOfCalls += argsValue;

  auto currentNumberOfCalls =
    v8::Number::New(isolate, static_cast<double>(numberOfCalls));

  args.GetReturnValue().Set(currentNumberOfCalls);
}

void Initialize(v8::Local<v8::Object> exports) {
  NODE_SET_METHOD(exports, "whoami", WhoAmI);
  NODE_SET_METHOD(exports, "myarray", myArray);
  NODE_SET_METHOD(exports, "increment", Increment);
}

NODE_MODULE(module_name, Initialize)