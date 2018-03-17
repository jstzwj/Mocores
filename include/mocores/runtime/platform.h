#ifndef PLATFORM_H
#define PLATFORM_H
//判断系统
#ifdef __CYGWIN__
#define MOCORES_OS_CYGWIN 1
#elif defined __SYMBIAN32__
# define MOCORES_OS_SYMBIAN 1
#elif defined _WIN32
# define MOCORES_OS_WINDOWS 1

#ifdef _WIN32_WCE
#define MOCORES_OS_WINDOWS_MOBILE 1
#elif defined(__MINGW__) || defined(__MINGW32__)
#define MOCORES_OS_WINDOWS_MINGW 1
#else
#define MOCORES_OS_WINDOWS_DESKTOP 1
#endif  // _WIN32_WCE

#elif defined __APPLE__
#define MOCORES_OS_MAC 1

#if TARGET_OS_IPHONE
#define MOCORES_OS_IOS 1
#if TARGET_IPHONE_SIMULATOR
#define MOCORES_OS_IOS_SIMULATOR 1
#endif

#endif

#elif defined __linux__
#define MOCORES_OS_LINUX 1
#if defined __ANDROID__
#define MOCORES_OS_LINUX_ANDROID 1
#endif
#elif defined __MVS__
#define MOCORES_OS_ZOS 1
#elif defined(__sun) && defined(__SVR4)
#define MOCORES_OS_SOLARIS 1
#elif defined(_AIX)
#define MOCORES_OS_AIX 1
#elif defined(__hpux)
#define MOCORES_OS_HPUX 1
#elif defined __native_client__
#define MOCORES_OS_NACL 1
#elif defined __OpenBSD__
#define MOCORES_OS_OPENBSD 1
#elif defined __QNX__
#define MOCORES_OS_QNX 1
#endif  // __CYGWIN__

//判断环境是否完全支持c++11
#ifndef MOCORES_LANG_CXX11
# if __GXX_EXPERIMENTAL_CXX0X__ || __cplusplus >= 201103L
// Compiling in at least C++11 mode.
#  define MOCORES_LANG_CXX11 1
# else
#  define MOCORES_LANG_CXX11 0
# endif
#endif

//判断系统是32位还是64位
#ifdef MOCORES_OS_WINDOWS
#	ifdef _WIN64
#	define MOCORES_OS_64
#	elif defined _WIN32
#	define MOCORES_OS_32
#	endif
#endif // MOCORES_OS_WINDOWS


#if defined(_MSC_VER) || defined (_WIN32) || defined(_WIN64)
#	include <windows.h>

#	ifndef __WINDOWS__
#		define __WINDOWS__ 1
#	endif

#	if defined(_WIN64) || defined(_M_X64) || defined(_M_AMD64)
#		define __WIN64__ 1
#	elif defined(_WIN32) || defined(_M_IX86)
#		define __WIN32__ 1
#	endif

#	undef EXPORT
#	undef CALL

#	undef min
#	undef max

#	undef RGB
#	undef RGBA

#	undef DELETE

#	if defined(MOCORES_BUILD_DLL_EXPORT)
#		define MOCORES_EXPORT __declspec(dllexport)
#		define MOCORES_EXPORT_WINONLY __declspec(dllexport)
#	else
#		define MOCORES_EXPORT __declspec(dllimport)
#		define MOCORES_EXPORT_WINONLY __declspec(dllimport)
#	endif

#	define MOCORES_CALL __stdcall
#	define MOCORES_INLINE __forceinline
#	define MOCORES_WONT_RETURN __declspec(noreturn)
#else
#	define MOCORES_EXPORT __attribute__ ((visibility("default")))
#	define MOCORES_EXPORT_WINONLY
#
#	define MOCORES_CALL
#	define MOCORES_INLINE inline
#	define MOCORES_WONT_RETURN
#endif

///unused variables
#define UNUSED(x) (void)x


#endif // PLATFORM_H
