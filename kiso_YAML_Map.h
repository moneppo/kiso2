/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class kiso_YAML_Map */

#ifndef _Included_kiso_YAML_Map
#define _Included_kiso_YAML_Map
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     kiso_YAML_Map
 * Method:    initialize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_kiso_YAML_Map_initialize
  (JNIEnv *, jobject);

/*
 * Class:     kiso_YAML_Map
 * Method:    getString
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_kiso_YAML_Map_getString
  (JNIEnv *, jobject, jstring);

/*
 * Class:     kiso_YAML_Map
 * Method:    getBoolean
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_kiso_YAML_Map_getBoolean
  (JNIEnv *, jobject, jstring);

/*
 * Class:     kiso_YAML_Map
 * Method:    getNumber
 * Signature: (Ljava/lang/String;)D
 */
JNIEXPORT jdouble JNICALL Java_kiso_YAML_Map_getNumber
  (JNIEnv *, jobject, jstring);

/*
 * Class:     kiso_YAML_Map
 * Method:    getSequence
 * Signature: (Ljava/lang/String;)Lkiso/YAML/Sequence;
 */
JNIEXPORT jobject JNICALL Java_kiso_YAML_Map_getSequence
  (JNIEnv *, jobject, jstring);

/*
 * Class:     kiso_YAML_Map
 * Method:    getMap
 * Signature: (Ljava/lang/String;)Lkiso/YAML/Map;
 */
JNIEXPORT jobject JNICALL Java_kiso_YAML_Map_getMap
  (JNIEnv *, jobject, jstring);

/*
 * Class:     kiso_YAML_Map
 * Method:    type
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_kiso_YAML_Map_type
  (JNIEnv *, jobject, jstring);

/*
 * Class:     kiso_YAML_Map
 * Method:    size
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_kiso_YAML_Map_size
  (JNIEnv *, jobject);

/*
 * Class:     kiso_YAML_Map
 * Method:    remove
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_kiso_YAML_Map_remove
  (JNIEnv *, jobject, jstring);

/*
 * Class:     kiso_YAML_Map
 * Method:    setString
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_kiso_YAML_Map_setString
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     kiso_YAML_Map
 * Method:    setBoolean
 * Signature: (Ljava/lang/String;Z)V
 */
JNIEXPORT void JNICALL Java_kiso_YAML_Map_setBoolean
  (JNIEnv *, jobject, jstring, jboolean);

/*
 * Class:     kiso_YAML_Map
 * Method:    setNumber
 * Signature: (Ljava/lang/String;D)V
 */
JNIEXPORT void JNICALL Java_kiso_YAML_Map_setNumber
  (JNIEnv *, jobject, jstring, jdouble);

/*
 * Class:     kiso_YAML_Map
 * Method:    setSequence
 * Signature: (Ljava/lang/String;Lkiso/YAML/Sequence;)V
 */
JNIEXPORT void JNICALL Java_kiso_YAML_Map_setSequence
  (JNIEnv *, jobject, jstring, jobject);

/*
 * Class:     kiso_YAML_Map
 * Method:    setMap
 * Signature: (Ljava/lang/String;Lkiso/YAML/Map;)V
 */
JNIEXPORT void JNICALL Java_kiso_YAML_Map_setMap
  (JNIEnv *, jobject, jstring, jobject);

/*
 * Class:     kiso_YAML_Map
 * Method:    firstKey
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_kiso_YAML_Map_firstKey
  (JNIEnv *, jobject);

/*
 * Class:     kiso_YAML_Map
 * Method:    nextKey
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_kiso_YAML_Map_nextKey
  (JNIEnv *, jobject, jstring);

#ifdef __cplusplus
}
#endif
#endif
