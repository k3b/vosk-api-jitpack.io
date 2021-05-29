#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jstring JNICALL
Java_org_vosk_HelloNative_stringFromJNI(JNIEnv *env, jobject thiz) {
    std::string hello = "Hello from lib C++";
    return env->NewStringUTF(hello.c_str());
}
