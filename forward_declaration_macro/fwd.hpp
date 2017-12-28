#ifndef FWD_HPP
#define FWD_HPP
#define _GET_NTH_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, N, ...) N

#define _fe_0(_classCall, _namespaceCall, _closeNamespace, ...)
#define _fe_1(_classCall, _namespaceCall, _closeNamespace, x) _classCall(x)
#define _fe_2(_classCall, _namespaceCall, _closeNamespace, x, ...) _namespaceCall(x) _fe_1(_classCall, _namespaceCall, _closeNamespace, __VA_ARGS__) _closeNamespace()
#define _fe_3(_classCall, _namespaceCall, _closeNamespace, x, ...) _namespaceCall(x) _fe_2(_classCall, _namespaceCall, _closeNamespace, __VA_ARGS__) _closeNamespace()
#define _fe_4(_classCall, _namespaceCall, _closeNamespace, x, ...) _namespaceCall(x) _fe_3(_classCall, _namespaceCall, _closeNamespace, __VA_ARGS__) _closeNamespace()
#define _fe_5(_classCall, _namespaceCall, _closeNamespace, x, ...) _namespaceCall(x) _fe_4(_classCall, _namespaceCall, _closeNamespace, __VA_ARGS__) _closeNamespace()
#define _fe_6(_classCall, _namespaceCall, _closeNamespace, x, ...) _namespaceCall(x) _fe_5(_classCall, _namespaceCall, _closeNamespace, __VA_ARGS__) _closeNamespace()
#define _fe_7(_classCall, _namespaceCall, _closeNamespace, x, ...) _namespaceCall(x) _fe_6(_classCall, _namespaceCall, _closeNamespace, __VA_ARGS__) _closeNamespace()
#define _fe_8(_classCall, _namespaceCall, _closeNamespace, x, ...) _namespaceCall(x) _fe_7(_classCall, _namespaceCall, _closeNamespace, __VA_ARGS__) _closeNamespace()
#define _fe_9(_classCall, _namespaceCall, _closeNamespace, x, ...) _namespaceCall(x) _fe_8(_classCall, _namespaceCall, _closeNamespace, __VA_ARGS__) _closeNamespace()
#define _fe_10(_classCall, _namespaceCall, _closeNamespace, x, ...) _namespaceCall(x) _fe_9(_classCall, _namespaceCall, _closeNamespace, __VA_ARGS__) _closeNamespace()

#define _CALL_MACRO_X_FOR_EACH(x, y, z, ...) \
    _GET_NTH_ARG("ignored", ##__VA_ARGS__, \
_fe_10, _fe_9, _fe_8, _fe_7, _fe_6, _fe_5, _fe_4, _fe_3, _fe_2, _fe_1, _fe_0)(x, y, z, ##__VA_ARGS__)

#define _FWD_DECLARE_CLASS(cls) class cls;
#define _FWD_DECLARE_NAMESPACE(ns) namespace ns {
#define _FWD_DECLARE_CLOSENAMESPACE() }

//  force semicolon at the end
#define MACRO_END_(LINE) extern void some_inprobable_long_function_name ## LINE(void)
#define MACRO_END MACRO_END_(__LINE__)

//  you can pass up to _fe_X_ parameters
//  examples:
//
//   FWD_DECL(ns1, ns2, cl1)
//   expands to:
//   namespace ns1 {namespace ns2{class cl1;}}
//
//   FWD_DECL(cl1)
//   expands to:
//   class cl1;
//
//   empty or exceeded number of parameters causes compilation err

#define FWD_DECL(...) _CALL_MACRO_X_FOR_EACH(_FWD_DECLARE_CLASS, _FWD_DECLARE_NAMESPACE, _FWD_DECLARE_CLOSENAMESPACE, ##__VA_ARGS__) MACRO_END  // NOLINT

#endif  // FWD_HPP
