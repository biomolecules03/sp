#include <stdio.h>
#include "DLL.h"
JNIEXPORT int JNICALL Java_DLL_add(JNIEnv *env, jobject javaobj, jint num1, jint num2) 
{
	return num1+num2;
}
