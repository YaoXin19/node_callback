#include <napi.h>
#include <thread>
#include <iostream>


// https://github.com/nodejs/node-addon-examples/tree/master/3_callbacks/node-addon-api
void SyncCallback(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Function cb = info[0].As<Napi::Function>();
  cb.Call(env.Global(), {Napi::String::New(env, "hello SyncCallback ")});
}


// https://github.com/nodejs/node-addon-api/blob/master/doc/threadsafe_function.md
Napi::ThreadSafeFunction tsfn;
std::thread nativeThread;
void AsyncCallback(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  tsfn= Napi::ThreadSafeFunction::New(
			info.Env(),
			info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
			"Resource Name",         // Name
			0,                       // Unlimited queue
			1,                       // Only one thread will use this initially
			[](Napi::Env) {        // Finalizer used to clean threads up
			  nativeThread.join();
		});

    nativeThread = std::thread([](){
      auto callback = []( Napi::Env env, Napi::Function jsCallback) {
      //try {
        jsCallback.Call(env.Global(), {Napi::String::New(env, "hello AsyncCallback")});
      //} catch(const std::exception& e) {
      // }
    };

    napi_status status = tsfn.BlockingCall(callback );
    tsfn.Release();
  });
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "syncCallback"), Napi::Function::New(env, SyncCallback));
  exports.Set(Napi::String::New(env, "asyncCallback"), Napi::Function::New(env, AsyncCallback));
  return exports;
}

NODE_API_MODULE(addon, Init)
