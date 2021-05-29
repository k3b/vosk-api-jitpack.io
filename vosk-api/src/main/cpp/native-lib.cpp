#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_de_k3b_android_hello_1cmake2_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}