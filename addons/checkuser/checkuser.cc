#pragma comment(lib, "netapi32.lib")

#include <napi.h>
#include <windows.h>
#include <lm.h>
#include <locale.h>

using namespace Napi;

Napi::Boolean CheckUser(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  setlocale(LC_ALL, "Rus");
  std::u16string username = info[0].As<Napi::String>().Utf16Value();

  DWORD dwlevel = 0;
  DWORD dwfilter = 0;
  USER_INFO_0 * theEntries;
  DWORD dwprefmaxlen = 512;
  DWORD dwentriesread;
  DWORD dwtotalentries;
  NET_API_STATUS result;

  result = NetUserEnum(NULL, dwlevel, dwfilter, (LPBYTE*)&theEntries, dwprefmaxlen, &dwentriesread, &dwtotalentries, NULL);
  for (int i = 0; i < dwentriesread; i++)  {
      std::wstring s(theEntries[i].usri0_name);
      std::u16string u16s(s.begin(), s.end());
      if (username == u16s) return Napi::Boolean::New(env, true);
  }
  NetApiBufferFree(theEntries);
  return Napi::Boolean::New(env, false);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "checkUser"),
              Napi::Function::New(env, CheckUser));
  return exports;
}

NODE_API_MODULE(checkuser, Init)