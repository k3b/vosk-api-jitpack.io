#include <jni.h>
#include <string>
#include "clonedRepositories/OpenBLAS/cblas.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_org_vosk_HelloNative_stringFromJNI(JNIEnv *env, jobject thiz) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_org_vosk_HelloNative_openblas_1set_1num_1threads(JNIEnv *env, jobject thiz, jint num_threads) {
    openblas_set_num_threads(num_threads);
}